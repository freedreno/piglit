/* [config]
 * expect_result: fail
 * glsl_version: 1.20
 * glsles_version: 1.00
 * [end config]
 *
 * From page 19 (page 25 of the PDF) of the GLSL 1.20 spec:
 *
 *     "When an array size is specified in a declaration, it must be an
 *     integral constant expression (see Section 4.3.3 "Constant Expressions")
 *     greater than zero."
 */


uniform float [vec2(2,2)] a;

void main() { gl_Position = vec4(a[0]); }
