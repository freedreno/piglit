/* [config]
 * expect_result: fail
 * glsl_version: 1.20
 * glsles_version: 1.00
 * [end config]
 *
 * From page 20 (page 26 of the PDF) of the GLSL 1.20 spec:
 *
 *     "There are no implicit array or structure conversions. For example, an
 *     array of int cannot be implicitly converted to an array of float."
 */


uniform vec3 a[2];

void main()
{
  ivec3 b[2];
  b = a;
  gl_Position = vec4(b[0].x, b[0].y, b[1].x, b[1].y);
}
