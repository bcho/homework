import pathlib
import re

import numpy as np
import tensorflow as tf


_name_pattern = re.compile(r'^(\w+)_\d+')


def _extract_class_name_from_image_name(name: str) -> str:
    m = _name_pattern.match(name)
    assert m is not None, f'invalid image name: {name}'
    return m.group(1)


class ImageDatasetLoader:

    def __init__(self, data_dir: pathlib.Path):
        self.data_dir = data_dir
        self._read_images_list()

    def _read_images_list(self):
        list_txt = self.data_dir / 'annotations' / 'list.txt'

        image_attrs = {}
        image_classes = set()
        with open(list_txt) as f:
            for line in f.readlines():
                if line.startswith('#'):
                    # comment line
                    continue
                ps = line.split(' ')
                if len(ps) != 4:
                    print('invalid line: {}'.format(line))
                    continue
                image_name = '{}.jpg'.format(ps[0])
                class_name = _extract_class_name_from_image_name(image_name)
                class_id, specie, breed_id = int(ps[1]), int(ps[2]), int(ps[3])
                image_attrs[image_name] = dict(
                    image_name=image_name,
                    class_id=class_id,
                    class_name=class_name,
                    specie=specie,
                    breed_id=breed_id,
                )
                image_classes.add(class_name)
        self.image_attrs = image_attrs
        self.image_classes = sorted(image_classes)

    def _read_image_and_label(self, image_file, label):
        image = tf.read_file(image_file)
        image = tf.image.decode_jpeg(image)
        image = tf.image.resize_images(image, [224, 224])
        image = tf.reshape(image, (1, 224, 224, 3))  # for resnet50

        return image, label

    def build_dataset(self) -> tf.data.Dataset:
        """Build tensorflow dataset from data dir.

        Returns:
            tensorflow dataset
        """
        images_dir = self.data_dir / 'images'
        images, labels = [], []

        for image in images_dir.glob('*.jpg'):
            images.append(image.absolute().as_posix())

            class_name = _extract_class_name_from_image_name(image.name)
            class_idx = self.image_classes.index(class_name)
            label = tf.one_hot(
                indices=[class_idx],
                depth=len(self.image_classes),
            )
            labels.append(label)

        images, labels = tf.constant(images), labels
        ds = tf.data.Dataset.from_tensor_slices((images, labels))
        return ds.map(self._read_image_and_label)

    def draw_images(self, ds: tf.data.Dataset, n=9):
        """Draw images from dataset.

        Args:
            ds: dataset
            n: first most n images to draw
        """
        import matplotlib.pyplot as plt

        cols = 3
        rows = n // cols
        n = rows * cols
        fig, ax = plt.subplots(ncols=cols, nrows=rows)

        it = ds.make_one_shot_iterator()
        b = it.get_next()
        i = 0
        with tf.Session() as s:
            while True:
                if i >= n:
                    break
                try:
                    image, label = s.run(b)
                except tf.errors.OutOfRangeError:
                    break
                class_idx = next(
                    idx for idx, i in enumerate(label[0]) if i == 1)
                class_name = self.image_classes[class_idx]

                image_data = np.asarray(image).astype(np.uint8)
                image_data = np.reshape(image_data, (224, 224, 3))
                image_fig = ax[i // 3, i % 3]
                image_fig.imshow(image_data)
                image_fig.set_title(class_name)
                i = i + 1
        fig.tight_layout()
