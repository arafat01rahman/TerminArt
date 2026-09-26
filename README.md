# TerminArt

Render an image as ASCII art in your terminal — either as ANSI true-color output
or as plain ASCII. It can also export a self-contained HTML file.

## Requirements

- A C++17 compiler (`g++`)
- OpenCV 4 development packages (`opencv4`), discoverable via `pkg-config`
  - Debian/Ubuntu: `sudo apt install build-essential pkg-config libopencv-dev`
  - Fedora: `sudo dnf install gcc-c++ pkgconf-pkg-config opencv-devel`

## Build

```bash
make
```

This compiles all sources under `src/` and produces the `termart` binary in the
project root. To remove build artifacts:

```bash
make clean
```

## Usage

```bash
./termart <image> [options]
```

### Options

| Flag | Description |
| --- | --- |
| `--width N` | Number of character columns (default `100`, allowed `1..500`) |
| `--color truecolor\|none` | `truecolor` (default) emits 24-bit ANSI color; `none` emits plain ASCII |
| `--html` | Write HTML instead of ANSI to the output file |
| `--output FILE` | Output file path (**required** with `--html`) |
| `-h`, `--help` | Show usage and exit |

Default color mode is `truecolor`, so running with no `--color` flag produces
24-bit ANSI output.

## Examples

True color (default), 80 columns wide:

```bash
./termart examples/building.jpg --width 80
```

Plain ASCII (no color codes):

```bash
./termart examples/messi.jpg --width 120 --color none
```

Export a standalone HTML file:

```bash
./termart examples/phodo.jpg --html --output art.html
```

There is also a convenience target that runs the default example:

```bash
make run
# equivalent to: ./termart examples/building.jpg --width 100
```

## What to expect

- **truecolor (default):** the image is printed as ASCII characters where each
  character is wrapped in a 24-bit ANSI foreground color escape
  (`ESC[38;2;R;G;Bm ... ESC[0m`). On a modern terminal this shows a full-color
  ASCII rendering. When piped to a file or a non-color terminal the escape
  sequences are still present.
- **`--color none`:** the same ASCII glyphs with no escape sequences — safe for
  plain-text logs and diffs.
- **`--html --output FILE`:** nothing is printed to the terminal; instead a
  complete HTML document is written to `FILE`. Open it in a browser to view the
  artwork.
- **Errors:** a missing/unreadable image or a bad flag prints
  `error: <message>` to stderr and exits with status `1`. A successful run exits
  with status `0`.
