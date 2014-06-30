// app.pde
//
// A demo application for ``relationship query program`` using Processing.js.
//
// You can double click in the canvas to generate a node. This node will have
// a random unique name. To attach a node to an existed family tree, you just
// need to drag it to any nodes in the family tree.
//
// To query a relationship (e.g. is Bob and Amy from same family?), you can
// type two names in the input box and press query button, the program will
// give you the answer.

// =====================
// CONSTANTS
// =====================
String[] US_NAMES = {
    "Aaron",
    "Abbey",
    "Abbie",
    "Abby",
    "Abdul",
    "Abe",
    "Abel",
    "Abigail",
    "Abraham",
    "Abram",
    "Babara",
    "Babette",
    "Bailey",
    "Bambi",
    "Bao",
    "Barabara",
    "Barb",
    "Barbar",
    "Barbara",
    "Caitlin",
    "Caitlyn",
    "Calandra",
    "Caleb",
    "Calista",
    "Callie",
    "Calvin",
    "Camelia",
    "Camellia",
    "Cameron",
    "Cami",
    "Dacia",
    "Dagmar",
    "Dagny",
    "Dahlia",
    "Daina",
    "Daine",
    "Daisey",
    "Daisy",
    "Dakota",
    "Dale",
    "Earl",
    "Earle",
    "Earlean",
    "Earleen",
    "Earlene",
    "Earlie",
    "Earline",
    "Earnest",
    "Earnestine",
    "Eartha"
};

color FG_COLOR = #FEFEFE;
color BG_COLOR = #000000;
color HI_COLOR = #17FF9B;
color NODE_COLOR = #4080BB;

float NODE_RADIUS = 50;
float NODE_KERNEL_RADIUS = 3;
float NODE_RADIUS_RATE = .75;

float FRAME_RATE = 25;

// =====================
// Global Components
// =====================
NodesCollection nc;

// =====================
// Main Routines
// =====================

void setup() {
    frameRate(FRAME_RATE);
    size(window.innerWidth, window.innerHeight - 50);

    nc = new NodesCollection();
}

void draw() {
    size(window.innerWidth, window.innerHeight - 50);
    background(BG_COLOR);
    
    nc.draw();
}

void mouseClicked() {
    nc.handleMouseClicked();
}

void mousePressed() {
    nc.handleMousePressed();
}

void mouseReleased() {
    nc.handleMouseReleased();
}


// =====================
// Exposed Interface
// =====================
NodesCollection getNC() {
    return nc;
}

// =====================
// Components
// =====================

/**
 * Node
 *
 * Represents a node.
 *
 * @param r node's radius.
 * @param x node's initial x position.
 * @param y node's initial y position.
 * @param name node's name.
 */
class Node {
    // Current r/x/y.
    float r, x, y;
    // Max (final) radius.
    float maximumR;
    String name;

    // pre-defined settings.
    color normalColor = NODE_COLOR;
    color highlightColor = HI_COLOR;
    color kernelColor = BG_COLOR;
    color nodeTextColor = FG_COLOR;
    float kernelRadius = NODE_KERNEL_RADIUS;
    float radiusRate = NODE_RADIUS_RATE;

    Node(float r_, float x_, float y_, String name_) {
        _setup(r_, x_, y_, name_);
    }

    void _setup(float r_, float x_, float y_, String name_) {
        r = 0;
        maximumR = r_;
        x = x_;
        y = y_;
        name = name_;
    }

    /**
     * If the mouse move into this node?
     */
    boolean isCointainedMouse() {
        return sq(x - mouseX) + sq(y - mouseY) < sq(r / 2);
    }

    /**
     * If the node near to other node?
     */
    boolean isNear(node otherNode) {
        float distance = sq((r + otherNode.r));

        return sq(x - otherNode.x) + sq(y - otherNode.y) < distance;
    }

    void increaseRadius() {
        if (r < maximumR) {
            r += min(maximumR - r, radiusRate);
        }
    }

    void draw() {
        noStroke();

        // Draw outer circle.
        if (isCointainedMouse()) {
            fill(highlightColor, 100);
        } else {
            fill(normalColor, 100);
        }
        ellipse(x, y, r, r);

        // Draw inner circle (kernel).
        fill(kernelColor, 100);
        ellipse(x, y, kernelRadius, kernelRadius);

        // Draw node name.
        fill(nodeTextColor, 100);
        text(name, x + r / 2, y - r / 2);

        increaseRadius();
    }
}


/**
 * NodesCollection
 *
 * Nodes manager.
 */
class NodesCollection {
    // Owned nodes.
    ArrayList nodes;

    int _draggingNodeIndex;
    boolean _dragging;
    float _draggingOffsetX;
    float _draggingOffsetY;

    int _mouseClickedTimes;
    float _mouseLastClickedTimeMS;
    float mouseClickIntervalMS = 500;

    NodesCollection() {
        nodes = new ArrayList();

        _draggingNodeIndex = -1;
        _dragging = false;
        _draggingOffsetX = 0.0;
        _draggingOffsetY = 0.0;

        _mouseClickedTimes = 0;
        _mouseLastClickedTimeMS = millis();
    }

    /**
     * Add a node to collection.
     *
     * The new node will have a random and unique name.
     *
     * @param x/y node's position.
     */
    void add(float x, float y) {
        String name = generateName();

        nodes.add(new Node(NODE_RADIUS, x, y, name));
    }

    /**
     * Draw nodes.
     */
    void draw() {
        Node node, neighbourNode;

        for (int i = nodes.size() - 1; i >= 0; i--) {
            node = (Node) nodes.get(i);

            if (i == _draggingNodeIndex && _dragging) {
                node.x = mouseX - _draggingOffsetX;
                node.y = mouseY - _draggingOffsetY;
            }

            node.draw();

            // Connect with neighbour node that near by.
            // FIXME it's O(N^2)
            for (int j = nodes.size() - 1; j >= 0; j--) {
                if (i == j) {
                    continue;
                }

                neighbourNode = (Node) nodes.get(j);
                if (node.isNear(neighbourNode)) {
                    stroke(HI_COLOR, 100);
                    line(node.x, node.y, neighbourNode.x, neighbourNode.y);
                }
            }
        }

        // Recheck when the nodes is updated.
        if (window.checkRelationship) {  // wraps for js side's timeout
          window.checkRelationship();
        }
    }

    String generateName() {
        String name;
        boolean conflictName;
        Node node;

        conflictName = true;
        while (conflictName) {
            name = US_NAMES[int(random(US_NAMES.length))];
            conflictName = false;

            for (int i = nodes.size() - 1; i >= 0; i--) {
                node = (Node) nodes.get(i);
                if (node.name == name) {
                    conflictName = true;
                    break;
                }
            }
        }

        return name;
    }

    /**
     * Hook for mouse clicked event.
     */
    void handleMouseClicked() {
        float nowMS = millis();

        if (nowMS - _mouseLastClickedTimeMS > mouseClickIntervalMS) {
            _mouseClickedTimes = 0;
        }

        _mouseClickedTimes++;

        if (_mouseClickedTimes == 2) {
            _mouseClickedTimes = 0;

            handleMouseDoubleClicked();
        }

        _mouseLastClickedTimeMS = nowMS;
    }

    /**
     * Hook for mouse double clicked event.
     */
    void handleMouseDoubleClicked() {
        // Add a node in current mouse position.
        if (nodes.size() < US_NAMES.length * 0.85) {
            add(mouseX, mouseY);

            // Recheck after adding a new node.
            window.checkRelationship();
        } else {
            console.log("Too many nodes.");
        }
    }

    /**
     * Hook for mouse pressed event.
     */
    void handleMousePressed() {
        // Select a dragging node.
        Node node;
        float dx, dy;

        for (int i = nodes.size() - 1; i >= 0; i--) {
            node = (Node) nodes.get(i);
            if (node.isCointainedMouse()) {
                _draggingNodeIndex = i;
                _draggingOffsetX = mouseX - node.x;
                _draggingOffsetY = mouseY - node.y;
                _dragging = true;

                break;
            }
        }
    }

    /**
     * Hook for mouse released event.
     */
    void handleMouseReleased() {
        _dragging = false;
        _draggingOffsetX = 0;
        _draggingOffsetY = 0;
        _draggingNodeIndex = -1;
    }
}
