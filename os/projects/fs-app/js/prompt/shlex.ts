/// <reference path="../_ref.d.ts" />

// @see https://gist.github.com/OllieTerrance/6280851
var shlex = (str): any => {
    var args = str.split(" ");
    var out = [];
    var lookForClose = -1;
    var quoteOpen = false;
    for (var x in args) {
        if (args.hasOwnProperty(x)) {
            var arg = args[x];
            var escSeq = false;
            for (var y in arg) {
                if (escSeq) {
                    escSeq = false;
                } else if (arg[y] === "\\") {
                    escSeq = true;
                } else if (arg[y] === "\"") {
                    quoteOpen = !quoteOpen;
                }
            }
            if (!quoteOpen && lookForClose === -1) {
                out.push(arg);
            } else if (quoteOpen && lookForClose === -1) {
                lookForClose = x;
            } else if (!quoteOpen && lookForClose >= 0) {
                var block = args.slice(lookForClose, parseInt(x) + 1).join(" ");
                var escSeq = false;
                var quotes = [];
                for (var y in block) {
                    if (escSeq) {
                        escSeq = false;
                    } else if (block[y] === "\\") {
                        escSeq = true;
                    } else if (block[y] === "\"") {
                        quotes.push(y);
                    }
                }
                var parts = [];
                parts.push(block.substr(0, quotes[0]));
                parts.push(block.substr(parseInt(quotes[0]) + 1, quotes[1] - (parseInt(quotes[0]) + 1)));
                parts.push(block.substr(parseInt(quotes[1]) + 1));
                block = parts.join("");
                out.push(block);
                lookForClose = -1;
            }
        }
    }
    return quoteOpen ? false : out;
}
