// [config]
// expect_result: fail
// glsl_version: 1.20
// glsles_version: 1.00
//
// # NOTE: Config section was auto-generated from file
// # NOTE: 'glslparser.tests' at git revision
// # NOTE: 6cc17ae70b70d150aa1751f8e28db7b2a9bd50f0
// [end config]

/* FAIL - local function declarations are not allowed. */
#version 120
void main() {
    float foo(float x);
    gl_FragColor = vec4(0.0, foo(0.5), 0.0, 1.0);
}

float foo(float x) {
    return x + 0.5;
}

