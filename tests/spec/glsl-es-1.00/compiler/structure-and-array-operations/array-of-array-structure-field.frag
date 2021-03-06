/* [config]
 * expect_result: fail
 * glsl_version: 1.20
 * glsles_version: 1.00
 * [end config]
 *
 * From page 19 (page 25 of the PDF) of the GLSL 1.20 spec:
 *
 *     "Only one-dimensional arrays may be declared."
 */


attribute vec4 vert;

struct S {
  vec4 [2] x[2];
};

void main()
{
  gl_FragData[0] = vec4(0.0);
}
