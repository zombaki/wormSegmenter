import io;

@dispatch=WORKER
(int x) worm(int i) "wormSegmenter" "0.0"
["set <<x>> [wormSegmenter_wormSegmenterF <<i>>]"];

int x = worm(1);
printf("Swift output is : %i",x);
