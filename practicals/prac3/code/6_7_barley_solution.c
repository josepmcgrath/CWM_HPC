/**************************************************
 *                                                *
 * First attempt at a code to calcule lost barley *
 * by A. Farmer                                   *
 * 18/05/18                                       *
 *                                                *
 **************************************************/

// Include any headers from the C standard library here
#include <stdio.h>

// Define any constants that I need to use here
#define PI 3.14
#define NUM_RADII 5

// This is where I should put my function prototypes
float area_of_circle(float outer_radius, float inner_radius); 

// Now I start my code with main()
int main() {

    // In here I need to delare my variables
    int   i=0;
    float outer_radius[NUM_RADII];
    float inner_radius[NUM_RADII];
    float area[NUM_RADII];
    float total_area;
    float loss_in_kg;

    // Next I need to get input from the user.
    // I'll do this by using a printf() to ask the user to input the radii.
    for(i=0; i<NUM_RADII; i++) {

    	printf("\nEnter outer radii %d:\t", i);
    	scanf("%f", &outer_radius[i]);
    	printf("Enter inner radii %d:\t", i);
    	scanf("%f", &inner_radius[i]);

	if(outer_radius[i] < inner_radius[i]) {
            printf("\n\n You've made an error! \n");
            printf(" Your outer radius is less that your inner radius \n\n");
            printf(" Please start the code again\n\n");
	    return(1);
	}
    }

    // Now I need to loop through the radii caluclating the area for each
    i=0;
    while(i<NUM_RADII) {
        area[i] = area_of_circle(outer_radius[i], inner_radius[i]);
        i++;
    }

    // Next I'll sum up all of the individual areas
    total_area = 0.0;
    for(i=0; i<NUM_RADII; i++) {
        total_area += area[i];
    }

    /******************************************************************
     *                                                                *
     * Now I know the total area I can use the following information: *
     *                                                                *
     * One square meter of crop produces about 135 grams of barley    *
     *                                                                *
     ******************************************************************/

    // Using the above I'll work out how much barley has been lost.
    loss_in_kg = total_area*0.135;

    // Finally I'll use a printf() to print this to the screen.
    printf("\nTotal area lossed in m^2 is:\t%f\n", total_area);
    printf("Total loss in kg is:\t\t%f\n", loss_in_kg);

    return(0);
}

// I'll put my functions here:
float area_of_circle(float outer_radius, float inner_radius) {
    float outer_area = PI * outer_radius * outer_radius;
    float inner_area = PI * inner_radius * inner_radius;
    float area = outer_area - inner_area;
    return area;
}

