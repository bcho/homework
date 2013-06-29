#coding: utf-8

import gtk
import gobject


class HelloWorld(object):

    def cb(self, widget, data):
        print 'Hello again - %s was pressed' % data

    def cb_delete(self, widget, event, data=None):
        gtk.main_quit()
        return False

    def cb_timeout(self, data=None):
        print data

    def __init__(self):
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)

        self.window.connect('delete_event', self.cb_delete)

        self.window.set_title('Hello Buttons!')
        self.window.set_border_width(10)

        self.box1 = gtk.HBox(False, 10)

        self.window.add(self.box1)

        self.button1 = gtk.Button('Button 1')
        self.button2 = gtk.Button('Button 2')
        self.button1.connect('clicked', self.cb, 'button 1')
        self.button2.connect('clicked', self.cb, 'button 2')

        self.box1.pack_start(self.button1, True, True, 0)
        self.box1.pack_start(self.button2, True, True, 0)

        self.button1.show()
        self.button2.show()
        self.box1.show()
        self.window.show()

        gobject.timeout_add(5000, self.cb_timeout, 'lol')

    def main(self):
        gtk.main()


if __name__ == '__main__':
    HelloWorld().main()
