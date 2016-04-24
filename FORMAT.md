# Formatting

For quite a while, I've been writing **very** sloppy code down, and that has made it hard for me to figure out what some parts of old code do.

Also, my code is ugly and inconsistent...

So here are basic rules I've written to remind myself:

## Line length

Lines shouldn't be longer than ~80 characters long.

## General Spacing

- **Tab: 4 Spaces**
- Space after commas
- Conditional & loop statements must have space after the syntax word, and no padding within parenthesis (e.g. `if (x)`, `while (x)`)
- Operators (e.g. `!=`) must be padded (e.g. `x == y`)
- Default argument assignment must have *no* padding (e.g. `void f(int x=0`))

### Curly braces

- Left (`{`) braces must be spaced before it for anything and cannot be solitary in a newline

Examples:

```
// What I DON'T want to see:
void f()
{ // Brace on a newline! Invalid!
    ...
}
// What I'd like to see:
void f() { // Brace on statement line = good
    ...
}
// Function that doesn't contain anything:
void empty() { } // acceptable!
```

- Right (`}`) braces, if enclosing a block of code, must be the at the same indentation as the statement
- If nothing is to be put inside curly braces, it must be spaced within (e.g. `int x[1] = { }`)
- When enclosing a block of code: the closing brace must be at the same indentation of the statement(*?*) before the left brace

Here is a visual on what I mean:

```
struct Y {
        ...
} // Notice the same indentation as 'struct'
```

### Classes

- No tabs before access modifiers
- Blocks of code in an access modifier should have a newline after it, *ONLY IF* there is another access modifier after it.

Visual:

```
public:
    Foo();

private:
    int bar;
```

- Inheriting from other classes should be on same line of class declaration (`class x`). Of course, with the exception if it exceeds the line limit, then, you'd have to move the colon (`:`) to the next line, along with the text following it
- That colon rule I just explained ^^: also applies to constructor initializer list
- Access modifiers should be used only *once*
- Access modifiers should be in the following order:
    - public
    - private
    - protected
- In any block of an access modifier: functions should be placed above variables, including a newline after it
- In `public`: functions that don't return a type (`void`) should be placed *before* others with return types
- If an access modifier is not needed, *don't* include it
- There should *not* be a newline before the closing bracket (`};`) of the class
- If a "getter" function only requires 1 line (e.g. `int getFoo()`), include it in the header file as one line
- Be `const`-correct!

Example of proper classes:

```
class Base {
public:
    Base(int x);
    void foo();
    int getBar() const { return m_bar; }

private:
    void car();

    int m_bar;

protected:
    bool m_b = true;
};
```

### "One-liner" if statements

Referring to `if (x) ...;` or

```
if (x)
    ...;
else
    ...;
```

If it can be fit into one line without surpassing the line limit, keep it in one line, **EXCEPT** when you have `if` and `else` (and `else if`). Else: put it on separate lines.

\* Also applies to `while` and `for`

### Switch statements

- Blocks of code after `case` must be indented, including `break`
- No newline before `case` or `default`

A proper switch statement should look like this:

```
switch (x) {
    case y:
        ...
        break;
    case z:
        ...
        break;
    default:
        ...
        break;
}
```

## Naming Conventions

- Variable names must start with a lowercase letter
- *Prefer* underscores instead of capital letters for separate words (e.g. `variable_name` rather than `variableName`), though I'm not going to be strict about this.
- Member variables must begin with `m_`

## Comments

### Single line

Referring to `//`, if it wasn't obvious :smile:

- Should be friendly reminders or quick reference of what something minor does, but **not** full documentation~

### Multi-line

Referring to `/* */`

- **Should be used for documenting** (and in some cases, can be used to comment out a section, thought `#if 0` is preferred)
- First line `/*` and closing `*/` should **not** have any text before or after, exception if it is a one-line documentation.
- Every line should start with an asterisk (`*`)
- The asterisks should be at the same indentation as `/*` and `*/`
- Proper punctuation.

**If documenting for functions:**

- If it returns a type, must have a separate line that starts with `returns: ` (ignores punctuation rule, I know!)

Examples:

```
// This is a nicely formatted doc:
/*
* Function for doing foo.
* returns: bar
*/
int foo();
// This is NOT:
/* Function for doing foo.
    * returns bar
    */
int foo();
```
