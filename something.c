/*
* Existence is a very complicated topic
* What we can determine is that things that exist are real, and things that dont exist
* aren't. Thats the definition after all.
*
* Its generally very hard to define existence without using recursive definitions,
* a definition exists, so therefore the definition of existence exists and so on.
*
* But what if the definition of existence didnt exist? Would existence be undefined?
* Would existence be non-existent? Well, existence exists... right?
*/

#define no_thing            0
#define is_something     != 0
#define is_nothing       == 0
#define THERE_EXISTS     extern

#define MAX_SIZE_OF_ANYTHING    1000

enum {
    DEFINITELY_NOTHING = 0,
    POSSIBLY_NOTHING = 1,
    POSSIBLY_SOMETHING = 2,
    DEFINITELY_SOMETHING = 3
};

typedef int existence_t;

typedef struct {
    void *pointer;
} memory_t;

typedef struct {
    void *something;
} something_t;

typedef struct {
    char *string;
} string_t;

/*
* Justify why you need memory. If the reason is not good enough, no memory will be given
* All hail malloc
*/
THERE_EXISTS memory_t malloc(int bytes, const char *reason);

/*
* return something just in case it returns something
*/
THERE_EXISTS something_t printf(const char *fmt, ...);

/*
 * we really shouldnt take existence for granted...
 */
THERE_EXISTS existence_t vsnprintf(char *buffer, int buffer_size, const char *fmt, __builtin_va_list ap);

/*
* give exit possibly something so it has hope that something exists
* after exit no matter the existence status of the code because
* hope always dies last, even after the process itself
*/
THERE_EXISTS existence_t exit(int code, int score);

/*
* copying might be bad but no successful person
* gained their status without copying
*   - some famous person
*/
THERE_EXISTS existence_t strcpy(char *dest, char *src);

/*
* make sure the file exists and is not nothing
*/
struct _IO_FILE;
typedef struct _IO_FILE FILE;

THERE_EXISTS FILE *stdin;

THERE_EXISTS existence_t fgets(const char *s, int size, FILE *fp);

THERE_EXISTS existence_t strcspn(const char *s, const char *something, const char *why_are_you_doing_this);

THERE_EXISTS int strlen(const char *s);

something_t something_from_possibly_nothing(memory_t possibly_nothing) {
    if (possibly_nothing.pointer is_something) {
        return (something_t) { .something = possibly_nothing.pointer };
    }
    return (something_t) { .something = no_thing };
}

string_t string_from_something_generic(something_t something) {
    /*
    * Is this "something" actually something or is it nothing
    * we often refer to nothing as something.
    * This has its roots deep inside math, where nothing (0) was
    * represented by something (the digit 0).
    *
    * While controversial, we can all agree that nothing is now something
    * hence this check
    */
    if (something.something is_nothing) {
        printf("Cannot create a string from nothing. Matter cannot be created nor destroyed");

        /*
         * Tell exit that there is possibly nothing
         * to "punish" it
         */
        exit(DEFINITELY_SOMETHING, POSSIBLY_NOTHING);
    }
    return (string_t) { .string = something.something };
}

void string_remove_newline(string_t string) {
    /*
    * We assume that the string is something thats not nothing
    * because if it was nothing it couldnt be a string, that has to
    * be something to exist
    */
    string.string[strcspn(string.string, "\n", "fgets gives me an extra newline which i want to remove")] = '\0';
}

string_t string_format_from(int size, const char *s, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, s);

    /*
     * If the size exceeds the max size of anything,
     * the produced string really something?
     */
    memory_t other_memory = malloc(size, "for vsnprintf");
    something_t other_thing = something_from_possibly_nothing(other_memory);
    if (other_thing.something is_nothing) {
        /*
        * Classic malloc refusing to give us memory for something
        * and instead giving us nothing
        */
        printf("Cannot create a string from nothing\n");
        exit(DEFINITELY_SOMETHING, POSSIBLY_NOTHING);
    }

    string_t other = string_from_something_generic(other_thing);

    vsnprintf(other.string, MAX_SIZE_OF_ANYTHING, s, ap);
    __builtin_va_end(ap);

    return other;
}

/*
 * The main function should exist, but if all goes well
 * it returns DEFINITELY_NOTHING, so then main doesnt exist
 * which also satisfies the return value of nothing
 * if main never existed to begin with
 */
existence_t main() {
    something_t something = something_from_possibly_nothing(malloc(MAX_SIZE_OF_ANYTHING, "I need it for something"));
    if (something.something is_nothing) {
        printf("There is something that is no thing so therefore something is nothing\n");
        exit(DEFINITELY_SOMETHING, POSSIBLY_SOMETHING);
    }
    string_t string = string_from_something_generic(something);

    printf("Enter something: ");
    fgets(string.string, MAX_SIZE_OF_ANYTHING, stdin);
    string_remove_newline(string);

    /*
     * The string should never be nothing
     */
    if (string.string is_something)
        printf("\"%s\" is certainly something\n", string.string);

    something_t something_new = something_from_possibly_nothing(malloc(MAX_SIZE_OF_ANYTHING, "I need it for something new"));
    if (something_new.something is_nothing) {
        printf("Something new cannot possibly be nothing, unless the original something was nothing\n");
        exit(DEFINITELY_SOMETHING, DEFINITELY_NOTHING);
    }
    string_t new_string = string_from_something_generic(something_new);

    printf("Now enter something that is nothing i have seen before: ");
    fgets(new_string.string, MAX_SIZE_OF_ANYTHING, stdin);
    string_remove_newline(new_string);

    /*
     * Much like before, the string is something
     */
    if (string.string is_something)
        printf("\"%s\" is probably something new\n", new_string.string);

    printf("We now have two old things: \"%s\" and the newer: \"%s\". Watch what happens when we combine them.\n"
           "We will produce something truly new\n", string.string, new_string.string);

    /*
     * If we request more than the max size of anything, is `newest_something` really something?
     */
    string_t newest_string = string_format_from(2 * MAX_SIZE_OF_ANYTHING, "%s%s", string.string, new_string.string);
    printf("The newest string that may or may not be something: \"%s\"\n", newest_string.string);
    printf("However, we produced something new that may or may not exist, from two definite existent strings\n");

    /*
    * Returning 0, aka returning the possibility of definite nothingness
    * is what we defined as success.
    * Success is not about having everything, or something, its always
    * about being nothing.
    */
    return DEFINITELY_NOTHING;
}
