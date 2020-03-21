//#include <config.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>

static double fun(double x)
{
  return x + cos(x*x);
}

int main (void)
{
  const double a = 1.0;
  const double b = 10.0;
  const int steps = 10;
  double xi, yi, x[100], y[100], dx;
  FILE *input, *output;
  int i;

  input = fopen("wartosci.txt", "w");
  output = fopen("gsl_interp_steffen.txt", "w");

  dx = (b-a) / (double) steps;

  for (i = 0; i <= steps; ++i) {
	  x[i] = a + (double)i * dx + 0.5 * sin((double)i * dx);
      y[i] = fun(x[i]);
      fprintf (input,"%g %g\n", x[i], y[i]);
  }

  {
    gsl_interp_accel *acc
      = gsl_interp_accel_alloc ();

    gsl_spline *spline
      = gsl_spline_alloc (gsl_interp_steffen, steps + 1);

    gsl_spline_init (spline, x, y, steps + 1);

    for (xi = a; xi <= b; xi += 0.01) {
        yi = gsl_spline_eval (spline, xi, acc);
        fprintf (output,"%g %g\n", xi, yi);
	}

    gsl_spline_free (spline);
    gsl_interp_accel_free(acc);
  }
  return 0;
}

//Porownanie roznych interpolacji
//Opisanie komend, screeny

//https://stackoverflow.com/questions/10792015/gnuplot-plotting-multiple-line-graphs
//https://stackoverflow.com/questions/40296851/gnuplot-log-plot-y-axis
//http://lowrank.net/gnuplot/plot3d2-e.html
//http://gnuplot-surprising.blogspot.com/2012/05/how-to-pick-out-maximum-and-minimum.html
//http://gnuplot.sourceforge.net/docs_4.2/node237.html
//http://gnuplot.sourceforge.net/demo/stats.html

// stats "dane2.dat" u 3 nooutput
// set label 1 "Maximun" at STATS_pos_max, STATS_max offset 1,-0.5
// set label 2 "Minimun" at STATS_pos_min, STATS_min offset 1,0.5
// splot "dane2.dat" w p pt 3 lc rgb"#ff0000" notitle, \
//      STATS_min w l lc rgb"#00ffff" notitle, \
//      STATS_max w l lc rgb"#00ffff" notitle

stats "dane2.dat" u 1:3 nooutput
a = STATS_pos_max_y
stats "dane2.dat" u 2:3 nooutput
b = STATS_pos_max_y
stats "dane2.dat" u 3 nooutput
c = STATS_max
set arrow 1 from -5, -2.1, c+5 to a,b,c fill
splot "dane2.dat" w p pt 3 lc rgb"#ff0000" notitle, \
     STATS_min w l lc rgb"#00ffff" notitle, \
     STATS_max w l lc rgb"#00ffff" notitle

n=100
max=3.
min=-3.
width=(max-min)/n
hist(x,width)=width*floor(x/width)+width/2.0
set xrange [min:max]
set yrange[-5:5]
set offset graph 0.05,0.05,0.05,0.0
set xtics min,(max-min)/5,max
set boxwidth width*0.82
set tics out nomirror
set xlabel "x"
set ylabel "Frequency"
plot 2*cos(x*sin(x)) smooth freq w boxes lc rgb"blue", \
    sin (x**5) lt rgb"#00ff00", \
    3*sin(x) lt rgb"red", \
    "fun1.txt" with yerrorbars lt rgb"red"