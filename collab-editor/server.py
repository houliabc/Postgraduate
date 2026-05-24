import json
import socket
from pathlib import Path

from aiohttp import web

PORT = 3001
HERE = Path(__file__).parent
HTML = (HERE / "index.html").read_text(encoding="utf-8")

strokes = []          # [{color, width, points: [{x,y},...]}]
clients = set()


async def index(_req):
    return web.Response(body=HTML, content_type="text/html", charset="utf-8")


async def ws_handler(req):
    ws = web.WebSocketResponse()
    await ws.prepare(req)
    clients.add(ws)

    # Sync existing strokes
    await ws.send_json({"type": "sync", "strokes": strokes})

    # Broadcast online count
    await _broadcast_count()

    try:
        async for msg in ws:
            if msg.type == web.WSMsgType.TEXT:
                try:
                    data = json.loads(msg.data)
                except json.JSONDecodeError:
                    continue

                if data["type"] == "stroke":
                    strokes.append(data["stroke"])
                    await _broadcast(data, exclude=ws)
                elif data["type"] == "clear":
                    strokes.clear()
                    await _broadcast(data, exclude=ws)

        # msg.type == CLOSE/ERROR → loop ends
    finally:
        clients.discard(ws)
        await _broadcast_count()

    return ws


async def _broadcast(data, exclude=None):
    msg = json.dumps(data)
    dead = set()
    for c in clients:
        if c is exclude:
            continue
        try:
            await c.send_str(msg)
        except Exception:
            dead.add(c)
    clients.difference_update(dead)


async def _broadcast_count():
    msg = json.dumps({"type": "count", "count": len(clients)})
    dead = set()
    for c in clients:
        try:
            await c.send_str(msg)
        except Exception:
            dead.add(c)
    clients.difference_update(dead)


def get_lan_ip():
    """Return the LAN IPv4 address."""
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(("8.8.8.8", 80))
        return s.getsockname()[0]
    except Exception:
        return "127.0.0.1"
    finally:
        s.close()


if __name__ == "__main__":
    app = web.Application()
    app.router.add_get("/", index)
    app.router.add_get("/ws", ws_handler)

    lan_ip = get_lan_ip()
    print(f"\n  [OK] 协作画板已启动 (Python)\n")
    print(f"  本机访问: http://localhost:{PORT}")
    print(f"  局域网访问: http://{lan_ip}:{PORT}")
    print(f"\n  分享局域网地址给其他人即可同步画图\n")

    web.run_app(app, host="0.0.0.0", port=PORT, print=lambda *_: None)
