/// <reference path="../_ref.d.ts" />

class FilesTreeView extends Backbone.View<Backbone.Model> {

    $el: JQuery;
    
    protected ft: FilesTree;
    protected fileTmpl = _.template(html.filesTreeFile);
    protected dirTmpl = _.template(html.filesTreeDir);
    protected subTreeTmpl = _.template(html.filesTreeSubtree);

    constructor(opts?: any) {
        super(opts);

        this.ft = FilesTree.getInstance();

        this.listenTo(this.ft, 'cwd:changed', this.render);
        this.listenTo(this.ft, 'fs:flushed', this.flush);
    }

    events(): any {
        return {
            'click a[data-path]': 'chdir'
        };
    }

    flush(): void {
        this.render();
        this.delegateEvents();
    }

    render(): FilesTreeView {
        var currentDir = this.ft.getCurrentDir(),
            entries = currentDir.getEntriesTo();

        var info = (cur: FileEntryModel) => {
            return [
                'Owner: '  + cur.get('oid'),
                'Created at: ' + cur.get('ctime'),
                'Edited at: ' + cur.get('mtime')
            ].join("\n");
        }

        var entryTemplate = (cur: FileEntryModel) => {
            var payload = cur.toJSON();
            payload['infos'] = info(cur);

            if (cur.isDir()) {
                return this.dirTmpl(payload);
            }

            return this.fileTmpl(payload);
        }

        var treeBuilder = (entries: FileEntryModel[]) => {
            if (entries.length === 0) {
                return '';
            }

            var cur = entries[0],
                remains = entries.slice(1),
                next = remains[0] || null;

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
        this.ft.chdir($(e.currentTarget).data('path'));

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
        this.listenTo(this.ft, 'fs:flushed', this.flush);
    }

    events(): any {
        return {
            'click a[data-path]': 'chdir'
        };
    }

    flush(): void {
        this.render();
        this.delegateEvents();
    }

    render(): FilesDirectoryView {
        var currentDir = this.ft.getCurrentDir();

        this.renderBreadcrumbs(currentDir);
        this.renderSubEntries(currentDir);

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

    protected renderSubEntries(currentDir: FileEntryModel): void {
        var entries = currentDir.getSubEntries();

        var dirTmpl = _.template(html.filesDirectoryDir),
            fileTmpl = _.template(html.filesDirectoryFile);

        var info = (cur: FileEntryModel) => {
            var owner = UserManager.getInstance().findUserByUid(cur.get('oid'));
            return [
                'Owner: '  + owner.get('name'),
                'Created at: ' + cur.get('ctime'),
                'Edited at: ' + cur.get('mtime')
            ].join("\n");
        }

        var icons = _.map(entries, (cur: FileEntryModel) => {
            var payload = cur.toJSON();
            payload['infos'] = info(cur);

            if (cur.isDir()) {
                return dirTmpl(payload);
            }

            return fileTmpl(payload);
        });

        $('.chart-stage', this.$el).html(icons.join("\n"));
    }

    protected chdir(e): boolean {
        this.ft.chdir($(e.currentTarget).data('path'));

        return false;
    }

}

class DiskUsageView extends Backbone.View<Backbone.Model> {
    
    $el: JQuery;

    protected disk: Disk;
    protected usedBlockTmpl = _.template(html.diskUsageUsed);
    protected unusedBlockTmpl = _.template(html.diskUsageUnused);
    
    constructor(opts?: any) {
        super(opts);

        this.disk = Disk.getInstance();

        this.listenTo(this.disk, 'disk:changed', this.render);
    }

    render(): DiskUsageView {
        var blocks = _.map(this.disk.getBlocksMap(), (node: boolean) => {
            return node ? this.usedBlockTmpl(node) : this.unusedBlockTmpl(node);
        });

        $('.disk-nodes', this.$el).html(blocks.join(''));

        return this;
    }
}
