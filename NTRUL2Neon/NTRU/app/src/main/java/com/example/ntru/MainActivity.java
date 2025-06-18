package com.example.ntru;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.ntru.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
   public native int runCCode();
    // Used to load the 'ntru' library on application startup.
    static {
        System.loadLibrary("ntru");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(runCCode());
    }

    /**
     * A native method that is implemented by the 'ntru' native library,
     * which is packaged with this application.
     */

}