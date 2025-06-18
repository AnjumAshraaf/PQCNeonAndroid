package com.example.pqckyberneon;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.pqckyberneon.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    public native int runCCode();
    // Used to load the 'pqckyberneon' library on application startup.
    static {
        System.loadLibrary("pqckyberneon");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        TextView tv = binding.sampleText;
        // Declare a native method

        // Get the result from native code
        int result = runCCode();
        tv.setText(String.valueOf(result));
    }

    /**
     * A native method that is implemented by the 'pqckyberneon' native library,
     * which is packaged with this application.
     */
   // public native String stringFromJNI();
}