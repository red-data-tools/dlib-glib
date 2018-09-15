# Dlib GLib

Dlib GLib is a wrapper library for [Dlib][dlib]. Dlib GLib
provides C API.

Dlib GLib supports [GObject Introspection][gobject-introspection].
It means that you can create language bindings at runtime or compile
time.

For example, you can use Dlib from Ruby by Dlib GLib and
[gobject-introspection gem][gobject-introspection-gem] with the
following code:

```ruby
# Generate bindings at runtime
require "gi"
DLIB = GI.load("DLIB")

# TODO
```

## Install

### How to build by users

You need to install the followings before you install Dlib GLib:

  * [Dlib][dlib]

  * [GObject Introspection][gobject-introspection]

  * [Meson][meson]

  * [Ninja][ninja]

You can build and install Dlib GLib after you install them:

```console
% mkdir -p build
% meson build --buildtype=release
% (cd build && ninja)
% (cd build && ninja install)
```

### How to build by developers

You need to install the followings before you install Dlib GLib:

  * [Dlib][dlib]

  * [GObject Introspection][gobject-introspection]

  * [Meson][meson]

  * [Ninja][ninja]

  * [GTK-Doc][gtk-doc]

```console
% mkdir -p build
% meson build -Dgtk_doc=true
% (cd build && ninja)
% (cd build && ninja install)
```

## Usage

TODO

## License

[Boost Software License][Boost Software License]. See LICENSE for details.

[dlib]:http://dlib.net/

[gobject-introspection]:https://wiki.gnome.org/Projects/GObjectIntrospection

[gobject-introspection-gem]:https://rubygems.org/gems/gobject-introspection

[meson]:http://mesonbuild.com/

[ninja]:https://ninja-build.org/

[gtk-doc]:https://www.gtk.org/gtk-doc/

[Boost Software License]:https://www.boost.org/users/license.html
