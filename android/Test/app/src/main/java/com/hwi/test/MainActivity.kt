package com.hwi.test

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.hwi.avcapture.HWCAVCapture
class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        var l=HWCAVCapture()

    }
}