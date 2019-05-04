import argparse
from dataclasses import dataclass
import pathlib
import sys

import tensorflow as tf
import tensornets as nets

from dataset import ImageDatasetLoader


@dataclass
class ResNet50TrainParameter:

    checkpoint_save_path: str

    learning_rate: float = 1e-5


def train_resnet50(
    image_data_loader: ImageDatasetLoader,
    parameter: ResNet50TrainParameter,
):
    classes = len(image_data_loader.image_classes)
    dataset = image_data_loader.build_dataset()

    inputs = tf.placeholder(tf.float32, [None, 224, 224, 3])
    outputs = tf.placeholder(tf.float32, [None, classes])
    model = nets.ResNet50(inputs, is_training=True, classes=classes)

    loss = tf.losses.softmax_cross_entropy(outputs, model)
    train = tf.train.GradientDescentOptimizer(parameter.learning_rate) \
        .minimize(loss)

    saver = tf.train.Saver()

    it = dataset.make_one_shot_iterator()
    get_next = it.get_next()
    with tf.Session() as sess:
        sess.run(model.pretrained())
        while True:
            try:
                image_data, label = sess.run(get_next)
            except tf.errors.OutOfRangeError:
                break
            sess.run(train, {inputs: image_data, outputs: label})

        save_path = saver.save(sess, parameter.checkpoint_save_path)
        print('model checkpoint saved to: {}'.format(save_path))


def main(_):
    data_dir = pathlib.Path(FLAGS.pet_data_dir)
    output_dir = pathlib.Path(FLAGS.output_dir)
    checkpoint_save_path = output_dir / 'resnet50'
    checkpoint_save_path.mkdir(exist_ok=True, parents=True)

    data_loader = ImageDatasetLoader(data_dir)
    train_parameter = ResNet50TrainParameter(
        checkpoint_save_path=checkpoint_save_path.as_posix(),
    )

    train_resnet50(data_loader, train_parameter)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--pet_data_dir',
        type=str,
        default='./data/pets',
    )
    parser.add_argument(
        '--output_dir',
        type=str,
        default='./data/model',
    )
    FLAGS, unparsed = parser.parse_known_args()
    with tf.Graph().as_default():
        tf.app.run(main=main, argv=[sys.argv[0]] + unparsed)
