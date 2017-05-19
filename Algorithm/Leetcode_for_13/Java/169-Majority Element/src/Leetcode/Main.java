package Leetcode;

public class Main {

//    int majorityElement(vector<int> &num) {
//        std::map<int, int> im;
//        for (int i = 0; i < num.size(); ++i){
//            map<int, int>::iterator it = im.find(num[i]);
//            if (it == im.end()) {
//                im[num[i]] = 1;
//            } else {
//                im[num[i]]++;
//            }
//            if (im[num[i]] > num.size()/2) {
//                return num[i];
//            }
//        }
//        return 0;
//    }
    public static void main(String[] args) {
	// write your code here

        int majorityElement(vector<int> &num) {
        int majority;
        int cnt = 0;
        for(int i=0; i<num.size(); i++){
            if ( cnt ==0 ){
                majority = num[i];
                cnt++;
            }else{
                majority == num[i] ? cnt++ : cnt --;
                if (cnt >= num.size()/2+1) return majority;
            }
        }
        return majority;
}
    }
}
