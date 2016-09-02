# StarSDR - Utilities for SDRs

# Installing the build dependencies

To build StarSDR, build tools will need to be installed. On most distros, the
build tools usually come as a single package/metapackage that are named
`build-essential`, `base-devel`, and similar. Additionally `pkg-config` and
development headers for `libusb` 1.0 should also be installed.

Here are some ways to install them on different distros.

Ubuntu/Debian and derivatives:

    $ sudo apt-get install build-essential pkg-config libusb-1.0-0-dev

Fedora:

    $ sudo yum groupinstall "Development Tools" "Development Libraries"
    $ sudo yum install libusb1 pkgconfig

Arch Linux:

    $ sudo pacman -Sy base-devel pkg-config libusb

Opensuse:

    $ sudo zypper install --type pattern devel_basis
    $ sudo zypper install pkg-config libusb-1_0

**Note:** If your distro is not covered here and you are not sure how to
install the build tools, try searching online for ‘build-essential equivalent
for *<your distro name here>*’.

# Compiling and installing

To compile and install, run the following commands:

    $ make installables
    $ sudo make install

By default, this results in libraries being installed in `/usr/local/sdr.d`,
and `rtl_biast` being installed in `/usr/local/bin`. If you want to change the
install location, use the `PREFIX` variable:

    $ sudo make PREFIX='/my/path' install
