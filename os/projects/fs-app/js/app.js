/// <reference path="./_ref.d.ts" />
/// <reference path="../_ref.d.ts" />
var __extends = this.__extends || function (d, b) {
    for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p];
    function __() { this.constructor = d; }
    __.prototype = b.prototype;
    d.prototype = new __();
};
var FileEntryModel = (function (_super) {
    __extends(FileEntryModel, _super);
    function FileEntryModel() {
        _super.apply(this, arguments);
    }
    FileEntryModel.prototype.defaults = function () {
        return {
            // Position in disk.
            startsAt: 0,
            endsAt: 0,
            // Ownership and permission.
            oid: 0,
            ownerPerm: 0,
            otherPerm: 0,
            // Type & stat.
            entryType: 0,
            ctime: 0,
            mtime: 0,
            // Sub entries.
            sub: []
        };
    };
    return FileEntryModel;
})(Backbone.Model);
var FS = (function (_super) {
    __extends(FS, _super);
    function FS() {
        _super.apply(this, arguments);
    }
    FS.prototype.getInstance = function () {
        if (!FS.instance) {
            FS.instance = new FS();
        }
        return FS.instance;
    };
    // Dump into files block.
    FS.prototype.store = function () {
        return '';
    };
    // Restore from files block.
    FS.prototype.restore = function (fileBlock) {
        return this;
    };
    FS.instance = null;
    return FS;
})(Backbone.Collection);
var Disk = (function () {
    function Disk() {
    }
    Disk.prototype.getInstance = function () {
        if (Disk.instance) {
            Disk.instance = new Disk();
        }
        return Disk.instance;
    };
    // Dump disk.
    Disk.prototype.store = function () {
        return '';
    };
    // Restore disk.
    Disk.prototype.restore = function (disk) {
        return this;
    };
    Disk.instance = null;
    return Disk;
})();
/// <reference path="../_ref.d.ts" />
var UserModel = (function (_super) {
    __extends(UserModel, _super);
    function UserModel() {
        _super.apply(this, arguments);
    }
    UserModel.prototype.defaults = function () {
        return {
            uid: 0,
            name: '',
            homeDir: '/'
        };
    };
    UserModel.prototype.getUid = function () {
        return this.get('uid');
    };
    UserModel.prototype.getName = function () {
        return this.get('name');
    };
    UserModel.prototype.getHomeDir = function () {
        return null;
    };
    return UserModel;
})(Backbone.Model);
var UserCollection = (function (_super) {
    __extends(UserCollection, _super);
    function UserCollection() {
        _super.apply(this, arguments);
    }
    // Dump users into user block.
    UserCollection.prototype.store = function () {
        return '';
    };
    // Restore users from user block.
    UserCollection.prototype.restore = function (userBlock) {
        return this;
    };
    return UserCollection;
})(Backbone.Collection);
/// <reference path="./_ref.d.ts" />
console.log('hello world');
console.log(UserModel);
