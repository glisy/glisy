#include <assert.h>
#include <glisy/gl.h>
#include <glisy/buffer.h>
#include "../test.h"

int
main (void) {
  glisy_buffer buffer;
  GLfloat data[] = {
    +1.0, -1.0,
    +0.0, +1.0,
    -1.0, -1.0
  };

  //TEST(({
    glisy_buffer_init(&buffer, GL_ARRAY_BUFFER);
    //glisy_buffer_bind(&buffer);
    //glisy_buffer_source(&buffer, sizeof(data), data);
    //glisy_buffer_update(&buffer, GL_STATIC_DRAW);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    //glisy_buffer_unbind(&buffer);
  //}));

  return 0;
}
