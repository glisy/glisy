#ifndef LIBSOP_H
#define LIBSOP_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * SOP types.
 */

typedef enum sop_enum sop_enum_t;
typedef struct sop_parser sop_parser_t;
typedef struct sop_parser_state sop_parser_state_t;
typedef struct sop_parser_options sop_parser_options_t;
typedef struct sop_parser_line_state sop_parser_line_state_t;

/**
 * This function pointer typedef defines the signature for a line callback
 */

typedef int (* sop_parser_line_cb) (const sop_parser_state_t *state,
                                    const sop_parser_line_state_t);

/**
 * SOP enum values.
 */

enum sop_enum {
  // Out of bounds state/value
  SOP_OOB = -1,

  // represents a empty state/value
  SOP_NULL = 0,

  // represents a comment value
  SOP_COMMENT,

  /**
   * OBJ directive types (http://www.martinreddy.net/gfx/3d/OBJ.spec)
   *
   * Vertex data:
   *  - geometric vertices (v)
   *  - texture vertices (vt)
   *  - vertex normals (vn)
   *  - face (f)
   */

  SOP_DIRECTIVE_VERTEX,
  SOP_DIRECTIVE_VERTEX_TEXTURE,
  SOP_DIRECTIVE_VERTEX_NORMAL,
  SOP_DIRECTIVE_FACE,

  /**
   * SOP errors
   */

  SOP_EOK,
  SOP_EMEM,
  SOP_EINVALID_OPTIONS,
  SOP_EINVALID_SOURCE,
};

/**
 * The associated callback fields defined in the SOP options
 * structure and the parser structure instance. We do this to avoid
 * defining a struct or typedef.
 */

#define SOP_PARSER_CALLBACK_FIELDS \
  sop_parser_line_cb ontexture;    \
  sop_parser_line_cb oncomment;    \
  sop_parser_line_cb onvertex;     \
  sop_parser_line_cb onnormal;     \
  sop_parser_line_cb onface;       \

/**
 * This structure represents the options available for initializing the
 * parser with state and callback function pointers.
 */

struct sop_parser_options {
  // user pointer given to sop_parser_state
  void *data;

  // user defined callbacks
  struct { SOP_PARSER_CALLBACK_FIELDS } callbacks;
};

/**
 * This structure reprents the current parsed line
 * in the OBJ file source when the parsers is executed
 * against a given source.
 */

struct sop_parser_line_state {
  // the directive type
  sop_enum_t type;

  // line directive
  const char *directive;

  // current line number of the source
  int lineno;

  // line data after directive
  void *data;

  // line data length after directive
  size_t length;
};

/**
 * This structure represents the current parser state.
 */

struct sop_parser_state {
  // user data pointer from sop_parser_options
  void *data;

  // pointer to the current state of the currently parsed line
  sop_parser_line_state_t *line;
};

/**
 * OBJ file format parser structure. This structure holds the state of the
 * parser and pointers to callback functions that should handle input from
 * OBJ content being parsed.
 */

struct sop_parser {
  // parser state that is updated when parsing an
  // OBJ file source
  sop_parser_state_t *state;

  // pointer to parser options
  const sop_parser_options_t *options;

  // user defined callbacks given from sop_parser_options
  struct { SOP_PARSER_CALLBACK_FIELDS } callbacks;
};

/**
 * Initializes SOP parser with options.
 */

int
sop_parser_init(sop_parser_t *parser,
                const sop_parser_options_t options);

/**
 * Execute SOP parser for a given source.
 */

int
sop_parser_execute(sop_parser_t *,
                   const char *source,
                   size_t length);

#ifdef __cplusplus
}
#endif
#endif
