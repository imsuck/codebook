# Acknowledgement
## NaCl - NCTU_a Contest library
Basically from the [ICPC codebook of team NCTU_a](https://github.com/ToxicPie/NaCl).

# Stuff
## Building

Run `make codebook` to build the PDF. 
Run `make help` for a list of build commands.

## Editing

Editing the codebook's content should be very simple, thanks to the automated 
TeX file generator. 

To add new content to the codebook, first put the files to add (code snippets 
or TeX files) somewhere under `src/`. You may also modify existing files.

To change the files to include, section names, or arrangements, etc., edit 
`codebook/config.yaml`. It should have a structure like this:

```yaml
include:
  - Section 1:
    - path_to_file
    - Subsection 1.1:
      - Subsubsection 1.1.1:
        - ...:
          - path_to_file
          - path_to_file
      - ...
    - ...
  - Section 2:
    - ...
  - ...
some_additional_configs:
  ...
```

Paths should be relative to `src/`. `.tex` files will be directly inputted, 
and other files will be shown as highlighted code. 
See the default config file for a complete example.

By default, all local dependencies for C/C++ files are shown. When there are 
`#include "..."` directives in a file, NaCl will show the section that the 
included file belongs to. It will also refuse to work if there is a dependency 
cycle. These behaviors can be changed in the config file.

`#include`s and comments of the form `/// ...` are removed, unless you add
`// keep-line` to the end of a line.

## Dependencies

-   A TeX distribution
-   Python 3.6 or newer
    -   `pyyaml` package
    -   `pygments` package
-   Clang-Format 13 or newer
-   Fira Mono font

## License

See [COPYING](COPYING.md) for details.
