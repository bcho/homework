// Pub-sub system.

export default {
    topics: {},

    sub: function(topic, cb) {
        if (this.topics[topic] === undefined) {
            this.topics[topic] = [];
        }
        this.topics[topic].push(cb);
    },

    pub: function(topic, payload) {
        if (this.topics[topic] === undefined) {
            return;
        }
        for (let i = 0; i < this.topics[topic].length; i++) {
            this.topics[topic][i](payload);
        }
    }

};
