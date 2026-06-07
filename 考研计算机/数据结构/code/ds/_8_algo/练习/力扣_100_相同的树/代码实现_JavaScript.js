/**
 * Definition for a binary tree node.
 * function TreeNode(val, left, right) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.left = (left===undefined ? null : left)
 *     this.right = (right===undefined ? null : right)
 * }
 */
/**
 * @param {TreeNode} p
 * @param {TreeNode} q
 * @return {boolean}
 */
// DFS
var isSameTree = function(p, q) {
    if (!p && !q) {
        return true
    } else if (!p || !q) {
        return false
    } else if (p.val != q.val) {
        return false
    }
    return isSameTree(p.left, q.left) && isSameTree(p.right, q.right)
};

// BFS
var isSameTree = function(p, q) {
    if (!p && !q) {
        return true
    } else if (!p || !q) {
        return false
    }

    const queue1 = [], queue2 = []
    queue1.push(p)
    queue2.push(q)
    while (queue1.length && queue2.length) {
        const node1 = queue1.shift()
        const node2 = queue2.shift()
        if (node1.val != node2.val) {
            return false;
        }
        const left1 = node1.left, right1 = node1.right
        const left2 = node2.left, right2 = node2.right
        if (left1 == null ^ left2 == null) {
            return false;
        }
        if (right1 == null ^ right2 == null) {
            return false;
        }
        if (left1 != null) {
            queue1.push(left1);
        }
        if (right1 != null) {
            queue1.push(right1);
        }
        if (left2 != null) {
            queue2.push(left2);
        }
        if (right2 != null) {
            queue2.push(right2);
        }
    }
    return !queue1.length && !queue2.length
}