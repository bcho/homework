/// <reference path="./_ref.d.ts" />

interface SerializableInterface {
    store(): string;
    restore(raw: string): SerializableInterface;
}
