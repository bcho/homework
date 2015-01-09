/// <reference path="./_ref.d.ts" />

interface SingletonInterface {
    getInstance(): SingletonInterface;
}

interface SerializableInterface {
    store(): string;
    restore(raw: string): SerializableInterface;
}
