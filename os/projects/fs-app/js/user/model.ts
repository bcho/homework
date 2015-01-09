/// <reference path="../_ref.d.ts" />

class UserModel extends Backbone.Model {
    
    defaults() {
        return {
            uid: 0,
            name: '',
            homeDir: '/'
        }
    }

    getUid(): number { return this.get('uid'); }
    getName(): number { return this.get('name'); }
    getHomeDir(): FileEntryModel { return null; }
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
