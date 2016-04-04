#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sop/sop.h>

static int
ontexture(const sop_parser_state_t *state,
          const sop_parser_line_state_t line) {
  return SOP_EOK;
}

static int
oncomment(const sop_parser_state_t *state,
          const sop_parser_line_state_t line) {
  return SOP_EOK;
}

static int
onvertex(const sop_parser_state_t *state,
         const sop_parser_line_state_t line) {
  return SOP_EOK;
}

static int
onnormal(const sop_parser_state_t *state,
         const sop_parser_line_state_t line) {
  return SOP_EOK;
}

static int
onface(const sop_parser_state_t *state,
       const sop_parser_line_state_t line) {
  return SOP_EOK;
}

int
sop_parser_init(sop_parser_t *parser,
                const sop_parser_options_t options) {
  if (!parser) return SOP_EMEM;
  memset(parser, 0, sizeof(sop_parser_t));
  parser->callbacks.ontexture = ontexture;
  parser->callbacks.oncomment = oncomment;
  parser->callbacks.onvertex = onvertex;
  parser->callbacks.onnormal = onnormal;
  parser->callbacks.onface = onface;
  memcpy(&parser->callbacks, &options.callbacks, sizeof(options.callbacks));
  parser->options = &options;
  return SOP_EOK;
}


int
sop_parser_execute(sop_parser_t *parser,
                   const char *source,
                   size_t length) {
  // handle poor state and input
  if (!parser) return SOP_EMEM;
  if (!source || 0 == length) return SOP_EINVALID_SOURCE;

  // sop state
  sop_parser_line_state_t line;
  sop_parser_state_t state;
  sop_enum_t type = SOP_NULL;

  // setup sate pointers
  state.line = &line;
  state.data = parser->options->data;

  // source state
  size_t bufsize = 0;
  char buffer[BUFSIZ];
  char prev = 0;
  char ch0 = 0;
  char ch1 = 0;
  int lineno = 0;
  int colno = 0;

  // init buffer
  memset(buffer, 0, BUFSIZ);

#define RESET_LINE_STATE {   \
  memset(buffer, 0, BUFSIZ); \
  lineno++;                  \
  bufsize = 0;               \
  colno = 0;                 \
}

  for (int i = 0; i < length; ++i) {
    ch0 = source[i];
    ch1 = source[i + 1];

    if (i > 0) {
      prev = source[i - 1];
    }

    if (' ' == ch0 && '\n' == prev) {
      RESET_LINE_STATE;
      continue;
    }

    if (' ' == ch0 && 0 == colno) {
      ch0 = ch1;
      ch1 = source[++i + 1];
    }

    // we've reached the end of the line and now need
    // to notify the consumer with a callback, state error,
    // or continue if there is nothing to do
    if ('\n' == ch0) {
      if (!bufsize) {
        RESET_LINE_STATE;
        continue;
      }
      line.data = 0;
      line.type = type;
      line.length = bufsize;
      switch (type) {
        // continue until something meaningful
        case SOP_NULL: break;

        // handle comments
        case SOP_COMMENT: {
          line.data = (void *) buffer;
          parser->callbacks.oncomment(&state, line);
          break;
        }

        // handle directives
        case SOP_DIRECTIVE_VERTEX_TEXTURE: {
          parser->callbacks.ontexture(&state, line);
          break;
        }

        case SOP_DIRECTIVE_VERTEX_NORMAL: {
          parser->callbacks.onnormal(&state, line);
          break;
        }

        case SOP_DIRECTIVE_VERTEX: {
          float vertex[4];
          sscanf(buffer, "%f %f %f %f",
              &vertex[0], &vertex[1], &vertex[2], &vertex[3]);
          line.data = vertex;
          parser->callbacks.onvertex(&state, line);
          break;
        }

        case SOP_DIRECTIVE_FACE: {
          unsigned int faces[3];
          sscanf(buffer, "%d %d %d", &faces[0], &faces[1], &faces[2]);
          line.data = faces;
          parser->callbacks.onface(&state, line);
          break;
        }

        // notify of memory errors
        case SOP_EMEM:
          return SOP_EMEM;

        // out of bounds if we get here for some reason
        default:
          return SOP_OOB;
      }

      RESET_LINE_STATE;
      continue;
    }

    if (0 == colno) {
      // v, vt, vn
      if ('v' == ch0) {
        if (' '== ch1) {
          type = SOP_DIRECTIVE_VERTEX;
          line.directive = "v";
        } else if ('t' == ch1) {
          type = SOP_DIRECTIVE_VERTEX_TEXTURE;
          (void) i++;
          line.directive = "vt";
        } else if ('n' == ch1) {
          type = SOP_DIRECTIVE_VERTEX_NORMAL;
          (void) i++;
          line.directive = "vn";
        } else {
          type = SOP_NULL;
        }
      } else if ('f' == ch0) {
        type = SOP_DIRECTIVE_FACE;
        line.directive = "f";
      } else if ('#' == ch0) {
        type = SOP_COMMENT;
        line.directive = "#";
      } else {
        type = SOP_NULL;
      }
    } else {
      buffer[bufsize++] = ch0;
    }

    colno++;
  }
  return SOP_EOK;
#undef RESET_LINE_STATE
}
