#if defined(__APPLE__) || defined(__linux__) || defined(__unix__)
	// Foreground
	#define FindianRed1 "\033[38;5;203m"
	#define FRojo3 "\033[38;5;160m"
	#define FSteelBlue1 "\033[38;5;75m"
	#define Chartreuse1 "\033[38;5;118m"
	// Background
	#define BLightGoldenRod1 "\033[38;5;227m"

	// Otros
	#define Bold "\033[1m"
	#define Reset "\033[0m"
	#define Dim "\e[2m"
#endif

#if defined(_WIN64)
	// Foreground
	#define FindianRed1 ""
	#define FRojo3 ""
	#define FSteelBlue1 ""

	// Background
	#define BLightGoldenRod1 ""

	// Otros
	#define Bold ""
	#define Reset ""
	#define Dim ""
#endif
