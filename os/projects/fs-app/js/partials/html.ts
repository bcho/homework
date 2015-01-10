module html {
 export var filesDirectoryBreadcrumbActive = ["<li class=\"active\">","    <%= name %>","</li>",""].join("\n");
export var filesDirectoryBreadcrumb = ["<li>","    <a><%= name %></a>","</li>",""].join("\n");
export var filesTreeDir = ["<li>","    <i class=\"fa fa-folder-o\"></i>","    <a><%= name %></a>","</li>",""].join("\n");
export var filesTreeFile = ["<li>","    <i class=\"fa fa-file-word-o\"></i>","    <%= name %>","</li>",""].join("\n");
export var filesTreeSubtree = ["<li>","    <i class=\"fa fa-folder-open-o\"></i>","    <a><%= name %></a>","</li>","<li class=\"files-tree-sub\">","    <ul class=\"files-tree\">","        <%= sub_tree %>","    </ul>","</li>",""].join("\n"); 
}
