<div align="center">
    <img src="https://allahcorp.com/static/assets/noble.png">
    Noble: No Bad Language Esoterics
</div>

## Manifest
> **Noble** is to get rid of esoterics in scripting languages and allow its users to integrate scripting to big-scale projects with a C++ based interpreter, standard library, and easily extendable base functions. Originally, it was created for the [`Gmeng`](https://github.com/catriverr/gmeng-sdk) Game Engine and kept as an internal tool (PLIB file reading). Now, it's being rewritten as a more extensive scripting language, not limited to Gmeng.

> [!NOTE]
> To learn more about Gmeng and it's documentation visit [`[gmeng.org]`](https://gmeng.org).

# Examples
While **Noble** can not currently execute scripts, we still have examples that the standard which defines Noble allows us to provide here.

`example.nb` / Writing "Hello, World!" to the console
```c
#import io;

// both 'fn' and 'function' keywords are accepted
fn main() {
    io::print("Hello, World!\n");
};
```
> the 'io' header is the standard library's input/output controller, and `print()` writes text to the first available interface
> ### Outputs:
> ```console
> $ noble example.nb
> Hello, World!
> ```

`example-internals.nb` / Internal Functions
```c
/// The standard of the Noble language
#import standard;
#import io;

fn main() {
    string info = standard::internals::get_execution_instance(main);
    /// internal info about the caller and definition of a function
    io::print("main() called from " << info.caller.name << " (from " << info.caller.file << ":" << info.caller.line << ")\n" <<
    "main() defined in: " << info.file << ":" << info.line << "\n");
};
```
> the 'standard' library provides internal functions and variables on the language.
> ### Outputs:
> ```console
> $ noble example-internals.nb
> main() called from noble.runner (from noble.internal:0)
> main() defined in: example-internals.nb:5
> ```
> (caller shows from noble.internal since it's the main() function)

## Contributing
Noble currently stands as a publically-accessable repository, but it does not accept commits to its main branch at this time. You are free to fork this repository to make changes as you wish.
