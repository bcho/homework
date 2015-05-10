import storage from '../../lib/storage';

describe('lib:storage', function() {

    storage.setStorage({});

    it('should store serializable value', function() {
        let serializable = {
                serialize: function() {
                    return 'test';
                }
            };

        storage.store('test', serializable).should.be.exactly(storage);
    });

    it('should get stored value', function() {
        let key ='test',
            expectedValue = 'test',
            serializable = {
                serialize: function() {
                    return expectedValue;
                }
            };

        storage.store(key, serializable);
        storage.restore(key).should.be.expectedValue;
        (storage.restore(key + 'invalid') == undefined).should.be.true;
    });

    it('should get stored value with class', function() {
        let key ='test',
            expectedValue = 'test',
            serializable = {
                serialize: function() {
                    return expectedValue;
                }
            };

        class S {
            constructor(content) { this.content = content; }

            static restore(content) { return new S(content); }
        }

        storage.store(key, serializable);
        storage.restoreWith(key, S).content.should.be.exactly(expectedValue);
        (storage.restoreWith(key + 'invalid', S) == null).should.be.true;
    })

});
