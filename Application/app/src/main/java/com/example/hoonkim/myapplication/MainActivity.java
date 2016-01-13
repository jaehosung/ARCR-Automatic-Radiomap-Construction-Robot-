package com.example.hoonkim.myapplication;


import android.content.Context;
import android.hardware.usb.UsbAccessory;
import android.hardware.usb.UsbManager;
import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.os.ParcelFileDescriptor;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedInputStream;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends Activity {

    TextView mText;
    UsbManager mUsbManager;
    UsbAccessory mAccessory;
    ParcelFileDescriptor mFileDescriptor;
    FileInputStream mInputStream;
    FileOutputStream mOutputStream;
    String mMessage;
    String mMessage2;
    String TAG = "DebugPy";

    int read_cnt;

    Runnable mUpdateUI = new Runnable() {
        @Override
        public void run() {
            mText.append(mMessage);
        }
    };

    Runnable mUpdateUI2 = new Runnable() {
        @Override
        public void run() {
            mText.append(mMessage2);
        }
    };

    Runnable mListenerTask = new Runnable() {
        @Override
        public void run() {

            read_cnt++;

//            mMessage = "!!! ";
//            mMessage += System.getProperty("line.separator");
//            mText.post(mUpdateUI);
//
//            MainActivity.this.runOnUiThread(new Runnable() {
//                public void run() {
//                    Toast.makeText(MainActivity.this, "read process " + read_cnt, Toast.LENGTH_SHORT).show();
//                }
//            });


            byte[] buffer = new byte[5];
            int ret;

            try {
                mMessage = ">>> ";
                ret = mInputStream.read(buffer); ;
                if (ret == 5) {
                    String msg = new String(buffer);
                    mMessage += msg + " read";
                } else {
                    mMessage += "Read error1";
                }

            } catch (IOException e) {
                e.printStackTrace();
                mMessage += "Read error2";
            }

            mMessage += System.getProperty("line.separator");
            mText.post(mUpdateUI);
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            new Thread(this).start();
        }
    };

    /** Called when the user clicks the Decrease/Increase button */
    public void sendMessage(View view) {

        char direction = 0;

        switch (view.getId()) {
            case R.id.actuator_decrease:
                direction = '1';
                break;
            case R.id.actuator_increase:
                direction = '0';
                break;
        }

        byte[] buffer = new byte[5];
        buffer[0] = (byte) 'A';
        for (int i = 1; i < 5; i++) {
            buffer[i] = (byte) direction;
        }

        mMessage2 = "<<< ";
        try {
            mOutputStream.write(buffer);
        } catch (IOException e) {
            e.printStackTrace();
            mMessage2 += "Send error";
        }
        String msg = new String(buffer);
        mMessage2 += msg + System.getProperty("line.separator");
        mText.post(mUpdateUI2);

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        read_cnt = 0;

        mText = (TextView) findViewById(R.id.display_area);
        mText.setMovementMethod(new ScrollingMovementMethod());

        Intent intent = getIntent();
        mUsbManager = (UsbManager) getSystemService(Context.USB_SERVICE);
        mAccessory = intent.getParcelableExtra(UsbManager.EXTRA_ACCESSORY);

        if (mAccessory == null) {
            mText.append("Not started by the Accessory directly" + System.getProperty("line.separator"));
            return;
        }

        Log.v(TAG, mAccessory.toString());
        mFileDescriptor = mUsbManager.openAccessory(mAccessory);
        if (mFileDescriptor != null) {
            FileDescriptor fd = mFileDescriptor.getFileDescriptor();
            mInputStream = new FileInputStream(fd);
            mOutputStream = new FileOutputStream(fd);
        }
        Log.v(TAG, mFileDescriptor.toString());
        new Thread(mListenerTask).start();

    }


}
