package org.legoboku.gdd2011;

import com.google.android.apps.gddquiz.IQuizService;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class Gdd2011Activity extends Activity {
    private IQuizService sampleServiceIf;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        Intent intent = new Intent(IQuizService.class.getName());
        bindService(
                intent,
                sampleServiceConn,
                BIND_AUTO_CREATE
        );
        
        Button button =  (Button) findViewById(R.id.button1);
        button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				try {
					TextView tv = new TextView(Gdd2011Activity.this);
				    tv.setText(sampleServiceIf.getCode());
				    setContentView(tv);
				} catch (RemoteException e) {
					e.printStackTrace();
				}
			}
        });    
    }
 
    private ServiceConnection sampleServiceConn = new ServiceConnection(){
		public void onServiceConnected(ComponentName name, IBinder service) {
            sampleServiceIf = IQuizService.Stub.asInterface(service);			
		}
		public void onServiceDisconnected(ComponentName name) {
			sampleServiceIf = null;
		}
    };
}
