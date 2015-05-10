let defaultStorage = {};

if (typeof window != 'undefined') {
    defaultStorage = localStorage;
}

export default {

    storage: defaultStorage,

    setStorage: function(storage) {
        this.storage = storage;
    },
    
    store: function(key, serializable) {
        this.storage[key] = JSON.stringify(serializable.serialize());

        return this;
    },

    restore: function(key) {
        let value = this.storage[key];
        if (value) {
            value = JSON.parse(value);
        }

        return value;
    },

    restoreWith: function(key, Klass) {
        let value = this.restore(key);
        if (value) {
            return Klass.restore(value);
        }

        return undefined;
    }
    
};
