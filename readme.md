## Example program / syntax demo

A program that continually increments a variable by 2 and prints the result:


	$test = int(10)
    forever >
        say(The value of test is now: $test)
        inc($test, 2)
        sleep(1)
    <

Output:

	The value of test is now: 10
	The value of test is now: 12
	The value of test is now: 14
	...
