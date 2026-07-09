//algoritmo busca por padrão de Naives

// C++ program for Naive Pattern 
// Searching algorithm 
#include <bits/stdc++.h> 
using namespace std; 

void search(char* pat, char* txt) 
{ 
	int M = strlen(pat); 
	int N = strlen(txt); 

	/* A loop to slide pat[] one by one */
	for (int i = 0; i <= N - M; i++) { 
		int j; 

		/* For current index i, check for pattern match */
		for (j = 0; j < M; j++) 
			if (txt[i + j] != pat[j]) 
				break; 

		if (j 
			== M) // if pat[0...M-1] = txt[i, i+1, ...i+M-1] 
			cout << "Pattern found at index " << i << endl; 
	} 
} 

// Driver's Code 
int main() 
{ 
	char txt[] = "AABAACAADAABAAABAA"; 
	char pat[] = "AABA"; 

	// Function call 
	search(pat, txt); 
	return 0; 
}

// KMP Algoritmo

// C++ program for implementation of KMP pattern searching 
// algorithm 
#include <bits/stdc++.h> 

void computeLPSArray(char* pat, int M, int* lps); 

// Prints occurrences of txt[] in pat[] 
void KMPSearch(char* pat, char* txt) 
{ 
	int M = strlen(pat); 
	int N = strlen(txt); 

	// create lps[] that will hold the longest prefix suffix 
	// values for pattern 
	int lps[M]; 

	// Preprocess the pattern (calculate lps[] array) 
	computeLPSArray(pat, M, lps); 

	int i = 0; // index for txt[] 
	int j = 0; // index for pat[] 
	while ((N - i) >= (M - j)) { 
		if (pat[j] == txt[i]) { 
			j++; 
			i++; 
		} 

		if (j == M) { 
			printf("Found pattern at index %d ", i - j); 
			j = lps[j - 1]; 
		} 

		// mismatch after j matches 
		else if (i < N && pat[j] != txt[i]) { 
			// Do not match lps[0..lps[j-1]] characters, 
			// they will match anyway 
			if (j != 0) 
				j = lps[j - 1]; 
			else
				i = i + 1; 
		} 
	} 
} 

// Fills lps[] for given pattern pat[0..M-1] 
void computeLPSArray(char* pat, int M, int* lps) 
{ 
	// length of the previous longest prefix suffix 
	int len = 0; 

	lps[0] = 0; // lps[0] is always 0 

	// the loop calculates lps[i] for i = 1 to M-1 
	int i = 1; 
	while (i < M) { 
		if (pat[i] == pat[len]) { 
			len++; 
			lps[i] = len; 
			i++; 
		} 
		else // (pat[i] != pat[len]) 
		{ 
			// This is tricky. Consider the example. 
			// AAACAAAA and i = 7. The idea is similar 
			// to search step. 
			if (len != 0) { 
				len = lps[len - 1]; 

				// Also, note that we do not increment 
				// i here 
			} 
			else // if (len == 0) 
			{ 
				lps[i] = 0; 
				i++; 
			} 
		} 
	} 
} 

// Driver program to test above function 
int main() 
{ 
	char txt[] = "ABABDABACDABABCABAB"; 
	char pat[] = "ABABCABAB"; 
	KMPSearch(pat, txt); 
	return 0; 
} 

//Algoritmo Rabin Karp:
/*
O algoritmo Rabin-Karp é um algoritmo usado para pesquisar/corresponder padrões no texto usando uma função hash. Ao contrário do algoritmo de correspondência de strings Naive, ele não percorre todos os caracteres na fase inicial, mas filtra os caracteres que não correspondem e, em seguida, realiza a comparação.

Rabin-Karp compara os valores de hash de uma string, em vez das strings em si. Para eficiência, o valor de hash da próxima posição no texto é facilmente calculado a partir do valor de hash da posição atual.

Funcionamento do algoritmo Rabin-Karp
Inicialmente calcule o valor de hash do padrão P.
Comece a iterar a partir do início da string:
Calcule o valor de hash da substring atual com comprimento m.
Se o valor de hash da substring atual e do padrão forem iguais, verifique se a substring é igual ao padrão.
Se forem iguais, armazene o índice inicial como uma resposta válida. Caso contrário, continue para as próximas substrings.
Retorne os índices iniciais como a resposta necessária.
*/

/* Following program is a C++ implementation of Rabin Karp 
Algorithm given in the CLRS book */
#include <bits/stdc++.h> 
using namespace std; 

// d is the number of characters in the input alphabet 
#define d 256 

/* pat -> pattern 
	txt -> text 
	q -> A prime number 
*/
void search(char pat[], char txt[], int q) 
{ 
	int M = strlen(pat); 
	int N = strlen(txt); 
	int i, j; 
	int p = 0; // hash value for pattern 
	int t = 0; // hash value for txt 
	int h = 1; 

	// The value of h would be "pow(d, M-1)%q" 
	for (i = 0; i < M - 1; i++) 
		h = (h * d) % q; 

	// Calculate the hash value of pattern and first 
	// window of text 
	for (i = 0; i < M; i++) { 
		p = (d * p + pat[i]) % q; 
		t = (d * t + txt[i]) % q; 
	} 

	// Slide the pattern over text one by one 
	for (i = 0; i <= N - M; i++) { 

		// Check the hash values of current window of text 
		// and pattern. If the hash values match then only 
		// check for characters one by one 
		if (p == t) { 
			/* Check for characters one by one */
			for (j = 0; j < M; j++) { 
				if (txt[i + j] != pat[j]) { 
					break; 
				} 
			} 

			// if p == t and pat[0...M-1] = txt[i, i+1, 
			// ...i+M-1] 

			if (j == M) 
				cout << "Pattern found at index " << i 
					<< endl; 
		} 

		// Calculate hash value for next window of text: 
		// Remove leading digit, add trailing digit 
		if (i < N - M) { 
			t = (d * (t - txt[i] * h) + txt[i + M]) % q; 

			// We might get negative value of t, converting 
			// it to positive 
			if (t < 0) 
				t = (t + q); 
		} 
	} 
} 

/* Driver code */
int main() 
{ 
	char txt[] = "GEEKS FOR GEEKS"; 
	char pat[] = "GEEK"; 

	// we mod to avoid overflowing of value but we should 
	// take as big q as possible to avoid the collison 
	int q = INT_MAX; 

	// Function Call 
	search(pat, txt, q); 
	return 0; 
} 

// This is code is contributed by rathbhupendra 

//Algoritmo Z

/*
If i > R then there is no prefix substring that starts before i and ends after i, so we reset L and R and compute new [L, R] by comparing str[0..] to str[i..] and get Z[i] (= R-L+1).

If i <= R then let K = i-L,  now Z[i] >= min(Z[K], R-i+1)  because str[i..] matches with str[K..] for atleast R-i+1 characters (they are in[L, R] interval which we know is a prefix substring). 
Now two sub cases arise:
If Z[K] < R-i+1  then there is no prefix substring starting at str[i] (otherwise Z[K] would be larger)  so  Z[i] = Z[K]and interval [L, R] remains same.
If Z[K] >= R-i+1 then it is possible to extend the [L, R] interval thus we will set L as i and start matching from str[R] onwards  and get new R then we will update interval [L, R] and calculate Z[i] (=R-L+1).
*/

// A C++ program that implements Z algorithm for pattern 
// searching 
#include <iostream> 
using namespace std; 

void getZarr(string str, int Z[]); 

// prints all occurrences of pattern in text using Z algo 
void search(string text, string pattern) 
{ 
	// Create concatenated string "P$T" 
	string concat = pattern + "$" + text; 
	int l = concat.length(); 

	// Construct Z array 
	int Z[l]; 
	getZarr(concat, Z); 

	// now looping through Z array for matching condition 
	for (int i = 0; i < l; ++i) { 
		// if Z[i] (matched region) is equal to pattern 
		// length we got the pattern 
		if (Z[i] == pattern.length()) 
			cout << "Pattern found at index "
				<< i - pattern.length() - 1 << endl; 
	} 
} 

// Fills Z array for given string str[] 
void getZarr(string str, int Z[]) 
{ 
	int n = str.length(); 
	int L, R, k; 

	// [L, R] make a window which matches with prefix of s 
	L = R = 0; 
	for (int i = 1; i < n; ++i) { 
		// if i>R nothing matches so we will calculate. 
		// Z[i] using naive way. 
		if (i > R) { 
			L = R = i; 

			// R-L = 0 in starting, so it will start 
			// checking from 0'th index. For example, 
			// for "ababab" and i = 1, the value of R 
			// remains 0 and Z[i] becomes 0. For string 
			// "aaaaaa" and i = 1, Z[i] and R become 5 
			while (R < n && str[R - L] == str[R]) 
				R++; 
			Z[i] = R - L; 
			R--; 
		} 
		else { 
			// k = i-L so k corresponds to number which 
			// matches in [L, R] interval. 
			k = i - L; 

			// if Z[k] is less than remaining interval 
			// then Z[i] will be equal to Z[k]. 
			// For example, str = "ababab", i = 3, R = 5 
			// and L = 2 
			if (Z[k] < R - i + 1) 
				Z[i] = Z[k]; 

			// For example str = "aaaaaa" and i = 2, R is 5, 
			// L is 0 
			else { 
				// else start from R and check manually 
				L = i; 
				while (R < n && str[R - L] == str[R]) 
					R++; 
				Z[i] = R - L; 
				R--; 
			} 
		} 
	} 
} 

// Driver program 
int main() 
{ 
	string text = "GEEKS FOR GEEKS"; 
	string pattern = "GEEK"; 
	search(text, pattern); 
	return 0; 
}

//Algoritmo Aho-Corasick:
/*
O algoritmo Aho-Corasick encontra todas as palavras em tempo O(n + m + z) onde z é o número total de ocorrências de palavras no texto. O algoritmo de correspondência de strings Aho-Corasick formou a base do comando Unix original "fgrep".

Pré-processamento: Construir um autômato de todas as palavras em arr[] O autômato tem principalmente três funções:

Ir para: Esta função simplesmente segue as arestas de Trie de todas as palavras em arr[].
É representado como uma matriz 2D g[][] onde armazenamos o próximo estado para o estado atual e caractere.

Falha: Esta função armazena todas as arestas que são seguidas quando o caractere atual não tem aresta em Trie.
É representado como uma matriz 1D f[] onde armazenamos o próximo estado para o estado atual.

Saída: Armazena índices de todas as palavras que terminam no estado atual.
É representado como uma matriz 1D o[] onde armazenamos índices de todas as palavras correspondentes como um bitmap para o estado atual.
*/
// C++ program for implementation of 
// Aho Corasick algorithm for String 
// matching 
#include <bits/stdc++.h> 
using namespace std; 

// Max number of states in the matching 
// machine. Should be equal to the sum 
// of the length of all keywords. 

#define MAXS 500 

// Maximum number of characters 
// in input alphabet 

#define MAXC 26 

// OUTPUT FUNCTION IS IMPLEMENTED USING out[] 
// Bit i in this mask is one if the word with 
// index i appears when the machine enters 
// this state. 
int out[MAXS]; 

// FAILURE FUNCTION IS IMPLEMENTED USING f[] 
int f[MAXS]; 

// GOTO FUNCTION (OR TRIE) IS 
// IMPLEMENTED USING g[][] 
int g[MAXS][MAXC]; 

// Builds the String matching machine. 
// arr - array of words. The index of each keyword is 
// important: 
//"out[state] & (1 << i)" is > 0 if we just found 
// word[i] in the text. 
// Returns the number of states that the built machine 
// has. States are numbered 0 up to the return value - 
// 1, inclusive. 

int buildMatchingMachine(string arr[], int k) 
{ 
	// Initialize all values in output function as 0. 
	memset(out, 0, sizeof out); 

	// Initialize all values in goto function as -1. 
	memset(g, -1, sizeof g); 

	// Initially, we just have the 0 state 
	int states = 1; 

	// Convalues for goto function, i.e., fill g[][] 
	// This is same as building a Trie for arr[] 
	for (int i = 0; i < k; i++) { 
		string word = arr[i]; 
		int currentState = 0; 

		// Insert all characters of current 
		// word in arr[] 
		for (int j = 0; j < word.length(); j++) { 
			int ch = word[j] - 'a'; 

			// Allocate a new node (create a new state) 
			// if a node for ch doesn't exist. 
			if (g[currentState][ch] == -1) 
				g[currentState][ch] = states++; 

			currentState = g[currentState][ch]; 
		} 

		// Add current word in output function 
		out[currentState] |= (1 << i); 
	} 

	// For all characters which don't have 
	// an edge from root (or state 0) in Trie, 
	// add a goto edge to state 0 itself 
	for (int ch = 0; ch < MAXC; ch++) 
		if (g[0][ch] == -1) 
			g[0][ch] = 0; 

	// Now, let's build the failure function 
	// Initialize values in fail function 
	memset(f, -1, sizeof f); 

	// Failure function is computed in 
	// breadth first order 
	// using a queue 
	queue<int> q; 

	// Iterate over every possible input 
	for (int ch = 0; ch < MAXC; ch++) { 

		// All nodes of depth 1 have failure 
		// function value as 0. For example, 
		// in above diagram we move to 0 
		// from states 1 and 3. 
		if (g[0][ch] != 0) { 
			f[g[0][ch]] = 0; 
			q.push(g[0][ch]); 
		} 
	} 

	// Now queue has states 1 and 3 
	while (!q.empty()) { 

		// Remove the front state from queue 
		int state = q.front(); 
		q.pop(); 

		// For the removed state, find failure 
		// function for all those characters 
		// for which goto function is 
		// not defined. 
		for (int ch = 0; ch < MAXC; ch++) { 

			// If goto function is defined for 
			// character 'ch' and 'state' 
			if (g[state][ch] != -1) { 

				// Find failure state of removed state 
				int failure = f[state]; 

				// Find the deepest node labeled by 
				// proper suffix of String from root to 
				// current state. 
				while (g[failure][ch] == -1) 
					failure = f[failure]; 
				failure = g[failure][ch]; 
				f[g[state][ch]] = failure; 

				// Merge output values 
				out[g[state][ch]] |= out[failure]; 

				// Insert the next level node 
				// (of Trie) in Queue 
				q.push(g[state][ch]); 
			} 
		} 
	} 
	return states; 
} 

// Returns the next state the machine will transition to 
// using goto and failure functions. currentState - The 
// current state of the machine. Must be between 
// 0 and the number of states - 1, 
// inclusive. 
// nextInput - The next character that enters into the 
// machine. 

// This function finds all occurrences of 
// all array words in text. 
void searchWords(string arr[], int k, string text) 
{ 

	// Preprocess patterns. 
	// Build machine with goto, failure 
	// and output functions 
	buildMatchingMachine(arr, k); 

	// Initialize current state 
	int currentState = 0; 

	// Traverse the text through the 
	// built machine to find all 
	// occurrences of words in arr[] 
	for (int i = 0; i < text.length(); i++) { 
		int ch = text[i] - 'a'; 

		// If goto is not defined, use 
		// failure function 
		while (g[currentState][ch] == -1) 
			currentState = f[currentState]; 
		currentState = g[currentState][ch]; 

		// If match not found, move to next state 
		if (out[currentState] == 0) 
			continue; 

		// Match found, print all matching 
		// words of arr[] 
		// using output function. 
		for (int j = 0; j < k; j++) { 
			if (out[currentState] & (1 << j)) 
				cout << "Word " << arr[j] 
					<< " appears from "
					<< i - arr[j].length() + 1 << " to "
					<< i << endl; 
		} 
	} 
} 
// Driver code 

int main() 
{ 
	string arr[] = { "he", "she", "hers", "his" }; 
	int k = sizeof(arr) / sizeof(arr[0]); 
	string text = "ahishers"; 
	searchWords(arr, k, text); 
	return 0; 
}


