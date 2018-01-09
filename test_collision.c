#include "amino.h"
#include "amino/rx/scene_fcl.h"
#include "amino.h"
#include "amino/rx/rxtype.h"
#include "amino/rx/scenegraph.h"
#include "amino/rx/scene_geom.h"
#include "amino/rx/scene_collision.h"
#include <pthread.h>

void* doCollision(void *sg);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;



size_t n;

double* TF_rel;
double* TF_abs;

void test_box()
{
    struct aa_rx_sg *sg = aa_rx_sg_create();

    struct aa_rx_geom_opt *opt_cl = aa_rx_geom_opt_create();
    aa_rx_geom_opt_set_collision(opt_cl, 1);


    aa_rx_sg_add_frame_fixed( sg,
                              "", "a",
                              aa_tf_quat_ident, aa_tf_vec_ident );
    aa_rx_sg_add_frame_fixed( sg,
                              "", "b",
                              aa_tf_quat_ident, aa_tf_vec_ident );



    double d[3] = {.1, .1, .1};
    aa_rx_geom_attach( sg, "a", aa_rx_geom_box(opt_cl, d) );
    aa_rx_geom_attach( sg, "b", aa_rx_geom_box(opt_cl, d) );



    aa_rx_sg_init(sg);
    aa_rx_sg_cl_init(sg);

	struct aa_rx_cl *cl = aa_rx_cl_create(sg);
	n = aa_rx_sg_frame_count(sg);
	double TF_relarr[7*n];
	double TF_absarr[7*n];
	TF_rel = TF_relarr;
	TF_abs = TF_absarr;

	aa_rx_sg_tf(sg, 0, NULL,
		    n,
		    TF_rel, 7,
		    TF_abs, 7 );



    pthread_t thread1, thread2;
    int retr1, retr2;

    retr1 = pthread_create(&thread1, NULL, doCollision, (void *) cl);
    retr2 = pthread_create(&thread2, NULL, doCollision, (void *) cl);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("thread 1: %d\n\r", retr1);
    printf("thread 2: %d\n\r", retr2);



}

void* doCollision(void* arg)
{
    struct aa_rx_cl *col = (struct aa_rx_cl*) arg;
	int is_collision;

	pthread_mutex_lock(&mutex);
	is_collision = aa_rx_cl_check(col, (size_t) n, TF_abs, 7, NULL);
	pthread_mutex_unlock(&mutex);


	printf("collision: %i\n\r", is_collision);
	assert ( is_collision );

}


int main( int argc, char **argv)
{
    (void) argc; (void) argv;
    aa_rx_cl_init();
    test_box();

    return 0;
}
