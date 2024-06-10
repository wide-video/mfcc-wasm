#include "LibrosaCpp/librosa/librosa.h"

using namespace std;

extern "C" {
	float* mfcc(int *pcm, int *len, int sr, 
		int n_fft, int n_hop, const string &win, bool center, const string &mode,
		float power, int n_mels, int fmin, int fmax, int n_mfcc, bool norm, int type) {

		vector<float> x(pcm, pcm + *len);
		vector<vector<float>> mfcc = librosa::Feature::mfcc(x, sr, n_fft, n_hop, win, center, mode, power, n_mels, fmin, fmax, n_mfcc, norm, type);

		*len = mfcc.size() * mfcc[0].size();
		float result[*len];
		int index = 0;

		for(int i = 0; i < mfcc.size(); ++i)
			for(int j = 0; j < mfcc[i].size(); ++j)
				result[index++] = mfcc[i][j];

		return result;
	}
}