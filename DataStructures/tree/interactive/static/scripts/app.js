(function () {
    var inputElem = document.querySelector('.input__stringify__form'),
        submitElem = document.querySelector('.input__stringify__submit-btn'),
        graphElem = document.querySelector('.graph__drawing'),
        graph;

    submitElem.addEventListener('click', function (e) {
        var tree;

        e.preventDefault();

        tree = Tree.fromString(inputElem.value);
        graph = new vis.Graph(graphElem, tree.visify(), {
            hierarchicalLayout: true
        });
    });
})();



function Tree() {
    this.id = null;
    this.level = null;
    this.value = null;
    this.parent = null;
    this.children = [];
}

Tree.prototype.addChild = function(node) {
    this.children.push(node);
    node.parent = this;
};

Tree.prototype.flat = function () {
    var rv = [this];

    for (var i = 0; i < this.children.length; i++) {
        rv = rv.concat(this.children[i].flat());
    }

    return rv;
};

Tree.prototype.visify = function () {
    var that = this,
        data = {
            nodes: [],
            edges: []
        },
        nodes = this.flat();

    // Mark node id & level.
    for (var i = 0; i < nodes.length; i++) {
        nodes[i].id = i;
        nodes[i].level = nodes[i].parent ? nodes[i].parent.level + 1 : 0;
    }

    for (var i = 0; i < nodes.length; i++) {
        data.nodes.push({
            id: nodes[i].id,
            label: nodes[i].value,
            level: nodes[i].level
        });

        for (var j = 0; j < nodes[i].children.length; j++) {
            data.edges.push({
                from: nodes[i].id,
                to: nodes[i].children[j].id
            });
        }
    }

    return data;
};

Tree.fromString = function (string) {
    var tokens = string
        .replace(/\(/g, ' ( ')
        .replace(/\)/g, ' ) ')
        .trim()
        .split(' ')
        .filter(function (x) { return x !== ''; }),
        tree;

    var readFrom = function (tokens) {
        var token,
            node,
            hasRoot;

        if (tokens.length === 0) {
            throw new TreeTokenizeException('Unexpected EOF while reading.');
        }
        token = tokens.shift();

        if (token === '(') {
            node = new Tree();
            hasRoot = false;
            while (tokens[0] !== ')') {
                child = readFrom(tokens);
                if (!hasRoot) {
                    hasRoot = true;
                    node.value = child.value;
                } else {
                    node.addChild(child);
                }
            }
            tokens.shift();
            return node;
        } else if (token === ')') {
            throw new TreeTokenizeException('Unexpected token ")"!');
        } else {
            node = new Tree();
            node.value = token;
            return node;
        }
    };

    return readFrom(tokens);
};

function TreeTokenizeException(message) {
    this.message = message;
    this.name = 'TreeTokenizeException';
}
