const http = require('http');
const fs = require('fs');
const path = require('path');
const { WebSocketServer } = require('ws');

const PORT = 3000;
const html = fs.readFileSync(path.join(__dirname, 'index.html'), 'utf-8');

const server = http.createServer((req, res) => {
  if (req.url === '/' || req.url === '/index.html') {
    res.writeHead(200, { 'Content-Type': 'text/html; charset=utf-8' });
    res.end(html);
  } else {
    res.writeHead(404);
    res.end('Not Found');
  }
});

const wss = new WebSocketServer({ server });

const strokes = [];   // { color, width, points: [{x,y}, ...] }
let clientCount = 0;

function send(ws, data) {
  if (ws.readyState === 1) ws.send(JSON.stringify(data));
}

function broadcast(data, exclude) {
  wss.clients.forEach(c => {
    if (c !== exclude) send(c, data);
  });
}

wss.on('connection', ws => {
  clientCount++;
  broadcast({ type: 'count', count: clientCount });

  // Sync all existing strokes to new client
  send(ws, { type: 'sync', strokes });

  ws.on('message', raw => {
    try {
      const data = JSON.parse(raw);
      if (data.type === 'stroke') {
        strokes.push(data.stroke);
        broadcast(data, ws);
      } else if (data.type === 'clear') {
        strokes.length = 0;
        broadcast(data, ws);
      }
    } catch (_) {}
  });

  ws.on('close', () => {
    clientCount--;
    broadcast({ type: 'count', count: clientCount });
  });

  ws.on('error', () => {});
});

server.listen(PORT, () => {
  const nets = require('os').networkInterfaces();
  console.log('\n  ✅ 协作画板已启动\n');
  console.log(`  本机访问: http://localhost:${PORT}`);
  for (const name of Object.keys(nets)) {
    for (const net of nets[name]) {
      if (net.family === 'IPv4' && !net.internal) {
        console.log(`  局域网访问: http://${net.address}:${PORT}`);
      }
    }
  }
  console.log('\n  分享局域网地址给其他人即可同步画图\n');
});
