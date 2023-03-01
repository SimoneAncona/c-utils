## string library
This library adds features to manage strings

```c
int main(int argc, char **argv) {
	string_t str = str_new_string("Hello, World!");
	string_t num = str_from_int(12);
	string_t str_num = str_concat(str, num); // Hello, World!12
}
```
### str_new_string
```c
string_t str_new_string(char_ptr_t s);
```
Returns a new string from a c string

### str_lower_case
```c
string_t str_lower_case(string_t s);
```
This function returns a new string equal to the give string but with the lower case characters.

### str_upper_case
```c
string_t str_upper_case(string_t s);
```
Returns a new string equal to the give string but with the upper case characters.

### str_substr
```c
string_t str_substr(string_t s, size_t start, size_t end);
```
Returns a sub string of the original string that starts from `start` (included) and ends to `end` (excluded)

### str_replace
```c
string_t str_replace(string_t s, string_t old_s, string_t new_s);
```
Finds the old string `old_s` from the original string `s` and replaces it with `new_s`

### str_concat
```c
string_t str_concat(string_t s1, string_t s2);
```
Returns a new string which is the result of the concatenation of the first to the second.

### str_from_char
```c
string_t str_from_char(char_t c);
```
This function returns a new string from the given character

### str_from_int
```c
string_t str_from_int(int_t n);
```
It returns the string representation of `n`

### str_from_int_base
```c
string_t str_from_int_base(int_t n, uint8_t base);
```
Same as `str_from_int` with the possibility of specifying the base (or radix)

### str_from_uint
```c
string_t str_from_uint(uint_t n);
```
It returns the string representation of `n`

### str_from_uint_base
```c
string_t str_from_uint_base(uint_t n, uint8_t base);
```