/**************************************************
 *                                                *
 * First attempt at a code to calcule lost barley *
 * by A. Farmer                                   *
 * 18/05/18                                       *
 *                                                *
 **************************************************/

// Include C standard lib headers.
#include <stdio.h>

// Define PI and the number of radii that I'm working with.
#define PI 3.14
#define NUM_RADII 5

// Function prototype for the area of a circle.
float area_of_circle(float outer_radius, float inner_radius); 

// Function prototype for the area of the field.
float area_of_field(float length_of_field, float width_of_field);

// Function to calculate the monetary loss.
float monetary_loss(float value_of_barley, float loss_in_kg);

// Declare main function. 
int main() {

    // Declare variables
    int   i = 0;

    float length_of_field   = 0.0f;
    float width_of_field    = 0.0f;
    float total_area_lost   = 0.0f;
    float total_area_field  = 0.0f;
    float value_of_barley   = 0.0f;
    float loss_in_kg        = 0.0f;
    float money_lost        = 0.0f;

    float outer_radius[NUM_RADII];
    float inner_radius[NUM_RADII];
    float area[NUM_RADII];

    // Get the length wand width of the field from the user
    printf("\nEnter the length of the field in meters:\t");
    scanf("%f", &length_of_field);
    printf("\nEnter the width of the field in meters:\t");
    scanf("%f", &width_of_field);

    // Now use the above input to find the area of the field.
    total_area_field = area_of_field(length_of_field, width_of_field);

    // Next loop over the radii getting the inner and outer radius.
    // If the object is a circle rather than a ring the user enters 0 for the inner radius
    for(i=0; i<NUM_RADII; i++) {

    	printf("\nEnter outer radii %d:\t", i);
    	scanf("%f", &outer_radius[i]);
    	printf("Enter inner radii %d:\t", i);
    	scanf("%f", &inner_radius[i]);

	// A quick error check to ensure the user doesn't create a negative area.
	if(outer_radius[i] < inner_radius[i]) {
            printf("\n\n You've made an error! \n");
            printf(" Your outer radius is less that your inner radius \n\n");
            printf(" Please start the code again\n\n");
	    return(1);
	}

	// A further error check to ensure all circles and rings are inside our field.
	if(length_of_field < outer_radius[i] || width_of_field < outer_radius[i]) {
            printf("\n\n This code will not work for spaceships that cannot park in a single field! \n");
	    return(1);
	}
    }

    // Calculate the areas for our rings or circles.
    i=0;
    while(i<NUM_RADII) {
        area[i] = area_of_circle(outer_radius[i], inner_radius[i]);
        i++;
    }

    // Sum all of the individual areas to give a total area.
    for(i=0; i<NUM_RADII; i++) {
        total_area_lost += area[i];
    }

    // Check to see if the total area of loss is bigger than the area of the field.
    if(total_area_lost > total_area_field) {
        printf(" You've lost all of your crop! \n\n");
        return(1);
    }

    /******************************************************************
     *                                                                *
     * Now I know the total area I can use the following information: *
     *                                                                *
     * One square meter of crop produces about 135 grams of barley    *
     *                                                                *
     * One kg of barley sells for about 10 pence                      *
     *                                                                *
     ******************************************************************/

    // Using the above calculate how much barley has been lost.

    // The value of 1 kg of barley:     
    value_of_barley = 0.1f;

    // The total number of kg lost:
    loss_in_kg = total_area_lost*0.135f;

    // Monetary loss: 
    money_lost = monetary_loss(value_of_barley, loss_in_kg);


    // Finally print out the results to screen.
    printf("\nTotal area lossed in m^2 is:\t%f\n", total_area_lost);
    printf("Total percentage lost is:\t%f\n", 100.0f*(total_area_lost/total_area_field));
    printf("Total loss in kg is:\t\t%f\n", loss_in_kg);
    printf("Total loss in GBP is:\t\t%f\n\n", money_lost);

    return(0);
}

// Function to calculate the area of the field:
float area_of_field(float length_of_field, float width_of_field) {
    float area = length_of_field * width_of_field;
    return area;
}


// Function to calculate the area of a ring or circle:
float area_of_circle(float outer_radius, float inner_radius) {
    float outer_area = PI * outer_radius * outer_radius;
    float inner_area = PI * inner_radius * inner_radius;
    float area = outer_area - inner_area;
    return area;
}

// Function to calculate the monetary loss:
float monetary_loss(float value_of_barley, float loss_in_kg) {
    float loss = value_of_barley * loss_in_kg;
    return loss;
}



