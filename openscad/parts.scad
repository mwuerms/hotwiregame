/**
 * Martin Egli
 * 2021-12-04
 * parts for vibra alarm 2
 */

module battery() {
    color("Silver")
    translate([0, 0, 0])
    cube([40, 22, 9]);
    color("Yellow")
    translate([40, 0, 0])
    cube([6, 22, 5]);
}

module chargerPCB() {
    color("Silver")
    translate([-2, (19-8)/2, 1])
    cube([6, 8, 3]);
    color("Blue")
    translate([0, 0, 0])
    cube([25, 19, 2]);
}

module arduinoMicroProPCB() {
    color("Silver")
    for(n = [0:1:5]) {
        translate([-13, 1+2.54/2+n*2.54, 1.75])
        cube([14, 1, 1]);
    }
    color("Black")
    translate([-1, 1, 1])
    cube([2.5, 16, 2.5]);
    color("Black")
    translate([15, 9.5, 1])
    rotate([0, 0, -45])
    cube([8, 8, 2]);
    color("Blue")
    translate([0, 0, 0])
    cube([34, 19, 2]);
}

module displayPCB() {
    color("Blue")
    translate([0, 0, 0])
    cube([27, 28, 1]);
    color("White")
    translate([0, 4.5, 0])
    cube([27, 19, 1.5]);
}

module switch() {
    color("Black")
    translate([0, 0, 0])
    cube([17, 13, 12]);
    color("Black")
    translate([-2, -2, 12])
    cube([17+4, 13+4, 2]);
    color("Red")
    translate([1.5, 1.5, 14])
    rotate([0, 15, 0])
    cube([14, 10, 4]);
    color("Silver")
    translate([0.5, (13-5)/2,-7])
    cube([1, 5, 7]);
    color("Silver")
    translate([17/2-0.5, (13-5)/2,-7])
    cube([1, 5, 7]);
}

module vibraMotor() {
    color("Silver")
    cylinder(d = 10, h = 3, $fn = 32);
}

vibraMotor();