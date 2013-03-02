#include <stdio.h>

#define INCH_METER 0.0254
#define FOOT_INCH 12

int main()
{
    int inch, foot;
    double meter;

    printf("input the foot and inch: ");
    scanf("%d %d", &foot, &inch);
    meter = (foot * FOOT_INCH + inch) * INCH_METER;
    printf("%d foot and %d inch = %lf meters", foot, inch, meter);

    return 0;
}
