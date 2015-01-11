/// <reference path="../_ref.d.ts" />

class UserModel extends Backbone.Model {
    
    defaults() {
        return {
            uid: 0,
            name: ''
        }
    }

    getUid(): number { return this.get('uid'); }
    getName(): number { return this.get('name'); }
    getHomeDir(): FileEntryModel {
        var homePath = 'home/' + this.getName();

        return FilesTree.getInstance().findByAbsolutePath(homePath);
    }
}


class UserCollection extends Backbone.Collection<UserModel> implements 
    SerializableInterface
{

    // Dump users into user block.
    store(): string {
        return '';
    }

    // Restore users from user block.
    restore(userBlock: string): UserCollection {
        return this;
    }
}


class UserManager extends Backbone.Events {

    private static instance: UserManager = null;

    protected currentUser: UserModel;
    protected users: UserCollection;

    static getInstance(): UserManager {
        if (! UserManager.instance) {
            UserManager.instance = new UserManager();
        }

        return UserManager.instance;
    }

    constructor() {
        // XXX Work around for extending from a object.
        _.extend(this, Backbone.Events);
    }

    // Get current user.
    getCurrentUser(): UserModel { return this.currentUser; }

    // Set current user.
    setCurrentUser(user: UserModel): UserManager {
        this.currentUser = user;

        this.trigger('current_user:changed');

        return this;
    }

    // Set users.
    setUsers(users: UserCollection): UserManager {
        this.users = users;

        this.trigger('users:changed');

        return this;
    }

    // Find an user by uid.
    findUserByUid(uid: number): UserModel {
        return this.users.findWhere({ uid: uid });
    }

    // Find an user by name.
    findUserByName(name: string): UserModel {
        return this.users.findWhere({ name: name });
    }

    // Get #users.
    getUsersCount(): number {
        return this.users.length;
    }
}
