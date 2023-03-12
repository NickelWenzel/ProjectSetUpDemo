# ProjectSetUpDemo

Just a minimal demo project to show case how to set up a C++ project that is being build with _CMake_, manages 3rd party dependencies with _Conan_ and uses _GitHub actions_ for CI integration.

# Building the project

### Presets

This project makes use of [presets][1] to simplify the process of configuring
the project. As a developer, you are recommended to always have the [latest
CMake version][2] installed to make use of the latest Quality-of-Life
additions.

As a developer, you should create a `CMakeUserPresets.json` file at the root of
the project:

```json
{
  "version": 2,
  "cmakeMinimumRequired": {
    "major": 3,
    "minor": 14,
    "patch": 0
  },
  "configurePresets": [
    {
      "name": "dev-<os>",
      "hidden": true,
      "inherits": ["conan", "ci-<os>"],
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Debug",
        "CMAKE_EXPORT_COMPILE_COMMANDS": "ON"
      }
    },
    {
      "name": "dev-debug",
      "binaryDir": "${sourceDir}/build/dev-debug",
      "inherits": "dev-<os>"
    },
    {
      "name": "dev-release",
      "binaryDir": "${sourceDir}/build/dev-release",
      "inherits": "dev-<os>",
      "cacheVariables": {
        "CMAKE_BUILD_TYPE": "Release"
      }
    }
  ],
  "buildPresets": [
    {
      "name": "dev-debug",
      "configurePreset": "dev-debug",
      "configuration": "Debug",
      "jobs": 4
    },
    {
      "name": "dev-release",
      "configurePreset": "dev-release",
      "configuration": "Release",
      "jobs": 4
    }
  ],
  "testPresets": [
    {
      "name": "dev-debug",
      "configurePreset": "dev-debug",
      "configuration": "Debug",
      "output": {
        "outputOnFailure": true
      },
      "execution": {
        "jobs": 4,
        "noTestsAction": "error"
      }
    },
    {
      "name": "dev-release",
      "configurePreset": "dev-release",
      "configuration": "Release",
      "output": {
        "outputOnFailure": true
      },
      "execution": {
        "jobs": 4,
        "noTestsAction": "error"
      }
    }
  ]
}
```

You should replace `<os>` in your newly created presets file with the name of
the operating system you have, which may be `win64`, `linux` or `darwin`. You
can see what these correspond to in the
[`CMakePresets.json`](CMakePresets.json) file.

`CMakeUserPresets.json` is also the perfect place in which you can put all
sorts of things that you would otherwise want to pass to the configure command
in the terminal.

### Dependency manager

The above preset will make use of the [conan][conan] dependency manager. After
installing it, download the dependencies and generate the necessary CMake
files by running this command in the project root:

```sh
conan install . -s build_type=<built_type> -b missing
```

You should replace `<build_type>` with either `Debug` or `Release` depending what configuration you want to build.

Note that if your conan profile does not specify the same compiler used by
CMake, then that could potentially cause issues. See the [conan docs][profile]
on profiles.

[conan]: https://conan.io/
[profile]: https://docs.conan.io/en/latest/using_packages/using_profiles.html

### Configure, build and test

If you followed the above instructions, then you can configure, build and test
the project respectively with the following commands from the project root on
any operating system with any build system:

```sh
cmake --preset=dev-<built_type>
cmake --build --preset=dev-<built_type>
ctest --preset=dev-<built_type>
```

You should replace `<build_type>` with either `debug` or `release` depending what configuration you want to build.

If you are using a compatible editor (e.g. VSCode) or IDE (e.g. CLion, VS), you
will also be able to select the above created user presets for automatic
integration.

Please note that both the build and test commands accept a `-j` flag to specify
the number of jobs to use, which should ideally be specified to the number of
threads your CPU has. You may also want to add that to your preset using the
`jobs` property, see the [presets documentation][1] for more details.

[1]: https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html
[2]: https://cmake.org/download/