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

        this.listenTo(this.ft, 'cwd:changed', this.render);
    }

    events(): any {
        return {
            'click a[data-path]': 'chdir'
        };
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

        var tree = treeBuilder(entries);
        $('.chart-stage .files-tree', this.$el).html(tree);

        return this;
    }

    protected chdir(e): boolean {
        var path = $(e.target).data('path');

        this.ft.chdir(path);

        return false;
    }

}

class FilesDirectoryView extends Backbone.View<Backbone.Model> {

    protected ft: FilesTree;
    $el: JQuery;

    constructor(opts?: any) {
        super(opts);

        this.ft = FilesTree.getInstance();

        this.listenTo(this.ft, 'cwd:changed', this.render);
    }

    events(): any {
        return {
            'click a[data-path]': 'chdir'
        };
    }

    render(): FilesDirectoryView {
        var currentDir = this.ft.getCurrentDir();

        this.renderBreadcrumbs(currentDir);

        return this;
    }

    protected renderBreadcrumbs(currentDir: FileEntryModel): void {
        var path = currentDir.getEntriesTo();

        var parentTmpl = _.template(html.filesDirectoryBreadcrumb),
            curTmpl = _.template(html.filesDirectoryBreadcrumbActive);

        path.pop();
        var parts = _.map(path, (p: FileEntryModel) => {
            return parentTmpl(p.toJSON());
        });

        parts.push(curTmpl(currentDir.toJSON()));

        $('.breadcrumb', this.$el).html(parts.join("\n"));
    }

    protected chdir(e): boolean {
        var path = $(e.target).data('path');

        this.ft.chdir(path);

        return false;
    }

}
