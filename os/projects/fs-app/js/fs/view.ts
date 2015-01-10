/// <reference path="../_ref.d.ts" />

class FilesTreeView extends Backbone.View<Backbone.Model> {

    protected ft: FilesTree;
    $el: JQuery;
    
    fileTmpl = _.template(html.filesTreeFile);
    dirTmpl = _.template(html.filesTreeDir);
    subTreeTmpl = _.template(html.filesTreeSubtree);

    constructor(opts?: any) {
        super(opts);

        this.ft = FilesTree.getInstance();

        // TODO listen on events
    }

    render(): FilesTreeView {
        var currentDir = this.ft.getCurrentDir(),
            entries = currentDir.getEntriesTo();

        var entryTemplate = (cur: FileEntryModel) => {
            if (cur.isDir()) {
                return this.dirTmpl(cur.toJSON());
            }

            return this.fileTmpl(cur.toJSON());
        }

        var treeBuilder = (entries: FileEntryModel[]) => {
            if (entries.length === 0) {
                return '';
            }

            var cur = entries[0],
                remains = entries.slice(1),
                next = remains[0] || null;

            if (! next) {
                return entryTemplate(cur);
            }

            var subTree = _.map(cur.getSubEntries(), (sub: FileEntryModel) => {
                if (sub === next) {
                    return treeBuilder(remains);
                }
                
                return entryTemplate(sub);
            });

            var payload = cur.toJSON();

            payload['sub_tree'] = subTree.join("\n");

            return this.subTreeTmpl(payload);
        };

        var tree = treeBuilder(entries.reverse());
        $('.chart-stage .files-tree', this.$el).html(tree);

        return this;
    }

}
