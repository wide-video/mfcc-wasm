#include "LibrosaCpp/librosa/librosa.h"

using namespace std;

extern "C" {
	float* mfcc(int *pcm, int *len, int sr, 
		int n_fft, int n_hop, const string &win, bool center, const string &mode,
		float power, int n_mels, int fmin, int fmax, int n_mfcc, bool norm, int type) {

		vector<float> v(pcm, pcm + *len);
		vector<vector<float>> mfcc = librosa::Feature::mfcc(v, sr, n_fft, n_hop, win, center, mode, power, n_mels, fmin, fmax, n_mfcc, norm, type);

		int x = mfcc.size();
		int y = mfcc[0].size();
		*len = x * y;
		float result[*len];
		int index = 0;

		for(int i = 0; i < x; ++i)
			for(int j = 0; j < y; ++j)
				result[index++] = mfcc[i][j];

		return result;
	}
}