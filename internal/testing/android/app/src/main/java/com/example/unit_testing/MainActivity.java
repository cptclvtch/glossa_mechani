package com.example.unit_testing;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.unit_testing.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'unit_testing' library on application startup.
    static {
        System.loadLibrary("unit_testing");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'unit_testing' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}