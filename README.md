# breakage
> Break your code and make it more secure.

## What is this?

**breakage** is a kind of [fuzzing](https://en.wikipedia.org/wiki/Fuzzing) tool for the [malloc(3)](https://www.man7.org/linux/man-pages/man3/malloc.3.html) family of functions.

At its core, it's a simple library that comes in between the real malloc and your program to intercept calls and randomize the output.

## Let's look at an example

Let's take this average C code here:
```c
char *my_strdup(char *str) {
    char *new_string = malloc(strlen(str) * sizeof(char) + 1);
    // Properly handle malloc failure here
    if (!new_string) {
        return NULL;
    }
    // ... strdup code ...
    return new_string;
}

int main(void) {
    // ..but forget here that `my_strdup` should also be protected
    char *heap_string = my_strdup("Hello, Vorld!");
    heap_string[7] = 'W'; // SIGSEGV, Segmentation fault.
    fprintf(stdout, "%s\n", heap_string);
    return 0;
}
```

You'd notice that the function call to `my_strdup` wasn't protected correctly. As a result, this function is vulnerable when `malloc` fails.

While this is obvious in this case, as your program grows in complexity, this can easily be overlooked, especially since `malloc` memory allocation errors are uncommon.

## How to use breakage

*****you might want to look at [How to build] first, just sayin'*****

This is when this tool comes into play: breakage is a shared library that, when loaded via [LD_PRELOAD](https://www.man7.org/linux/man-pages/man8/ld.so.8.html), intercepts `malloc` calls, and returns `NULL` at random.

You configure breakage via environment variables; here's somewhat of a configuration:

```bash
# LD_PRELOAD is mandatory, the rest are configuration options
LD_PRELOAD=path/to/breakage.so \
  BRK_DEBUG=1 \
  BRK_NO_LOG=1 \
  BRK_FAIL_CHANCE=5000 \ # TL;DR keep and change that
  ./minishell
```

- `LD_PRELOAD`
  - Allows for the library to load and MITM functions
- `BRK_DEBUG=1`
  - Setting this environment variable to anything will output debug messages
- `BRK_NO_LOG=1`
  - Setting this environment variable to anything will not display any logs (overwrites `BKR_DEBUG`)
- `BRK_FAIL_CHANCE`
  - Sets the fail chance to the provided value.

The "fail chance" is divided by 100 to allow for better randomization. As such, a `BKR_FAIL_CHANCE` value of `500` will result in `0.5%` of `malloc` calls to fail. Setting it to `10000` will fail 100% of calls.  
I'd recommend playing around with the values, it should give you a better rough understanding on how the targetted program works.

The debug mode will log any calls to `malloc` and `free`, might be useful for some.

## Other tidbits

This tool also has some small integrations with `readline` (and `add_history`) specifically so that it can be used for minishell :)

If you want to use it with something like `valgrind`, I'd suggest using the `env` GNU utility and tracking children. For example:

```bash
valgrind --trace-children=yes env LD_PRELOAD=$BREAKAGE BRK_FAIL_CHANCE=1000 BRK_NO_LOG=1 ./minishell
```

## How to build

breakage is written in Divine C; that is, C that follows the [42 Norm](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).

For build tools, you'll need a C compiler (`clang` is used here, but this can be changed), and GNU `make`.

To clone the repo, you can use Git:

```bash
# This will create a "breakage" folder in your current working directory
git clone https://github.com/seekrs/breakage.git

# Go into it
cd breakage
```

To build it, simply run:
```bash
make
```

This should produce a `libbreakage.so` in the directory.

You can now learn [How to use breakage].

## Future goals

This project is currently very much in its starting stages. 

My short term plan is having a command-line launcher similar to `valgrind` to more easily configure and use the damn thing.

Other ideas might contain:
- configuration file
- automatic stress-tester
  - you'd give the program input instructions, and it would use a finite state-machine to resolve hundred or thousand of configurations and test your program in those cases
- `malloc` usage analysis
  - for each possible configuration, try it out a couple of times to see how many calls to `malloc` have been made, then try all possible configurations (fail 1st, ok 2nd, etc.)
- lighter memory checker than valgrind (maybe???)

## License

This project is licensed under the [GPLv3 License](./LICENSE).
