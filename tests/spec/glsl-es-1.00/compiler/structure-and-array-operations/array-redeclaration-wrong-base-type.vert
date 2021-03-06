/* [config]
 * expect_result: fail
 * glsl_version: 1.20
 * glsles_version: 1.00
 * [end config]
 *
 * From page 19 (page 25 of the PDF) of the GLSL 1.20 spec:
 *
 *     "It is legal to declare an array without a size and then later
 *     re-declare the same name as an array of the same type and specify a
 *     size."
 */


float a_function(float[3]);
float a_function(vec4[3]);

void main()
{
  float [] an_array;

  an_array[0] = 0.0;
  an_array[1] = 1.0;
  an_array[2] = 2.0;

  vec4 [3] an_array;

  gl_Position = vec4(a_function(an_array));
}
