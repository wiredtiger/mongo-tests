require 'file-tail'
WORK_DIR="~/work"
MONGO_BIN="#{WORK_DIR}/mongo"
MONGO_DBPATH="#{WORK_DIR}/data"
YCSB_BIN="#{WORK_DIR}/ycsb/bin"
ycsb_log="ycsb.log"
YCSB_WORKLOAD="#{WORK_DIR}/evaluator/17157"
NUM_BAD_RUNS=5
DEBUG=0

def clean_mongo
	`pkill -9 mongod`
	sleep 5
	`rm -rf #{MONGO_DBPATH}/*`
end

def spawn_mongo
	clean_mongo
	`#{MONGO_BIN}/mongod --dbpath #{MONGO_DBPATH} --logpath #{MONGO_DBPATH}/mongod.log --storageEngine=wiredTiger --fork`
end

def spawn_ycsb(ycsb_log)
	p "#{YCSB_BIN}/ycsb load mongodb -s -P #{YCSB_WORKLOAD}"
	`#{YCSB_BIN}/ycsb load mongodb -s -P #{YCSB_WORKLOAD}`
        `#{YCSB_BIN}/ycsb run mongodb -s -P #{YCSB_WORKLOAD} > #{ycsb_log} 2>&1 &`
end

def evaluate(ycsb_log)

#Initial Variables
changefactor=1.1
started = false
average = 0
last = 0
done = false
#last round we were stable:0, rising:1, falling:2
rfs = 0
sustained = 0
initial = true
failsearch = false
fail = false
fh = File.open ycsb_log
fh.extend(File::Tail)
fh.tail do |line|
	if line.include? "[OVERALL]"
       		done = true
		return fail
        end
	unless done
                unless started
			if line.include? "mongo connection created"
				started = true
			end
		else
                    	curr = line.split()[4].to_f
			msg = "Currently got #{curr}"
			if average == 0
				average = curr
			else
				last = average
                                average = (average + curr)/2
				msg += " last is #{last}"
				#we increased by a margin
				if curr > last*changefactor && curr > last
					msg += " and we rose"
					#we fell, then rose. 
					if rfs != 1
						adj = (curr/last)-1
                                                if adj > 1
                                                        average = last unless initial
                                                else
							changefactor+=adj
                                                        msg += " and we incremeneted the change factor by #{adj} to #{changefactor}"
                                                end
					end
					sustained = 0
					# we rebounded. stop hunging for a fail
					failsearch = false
					if curr > last*(changefactor*2)
						average =  last	
					end
					rfs = 1
				#we decreased by a margin
				elsif curr < last/changefactor && curr < last
					msg += " and we fell"
					#we rose, then fell
					if rfs != 2
						adj = (last/curr)-1
						if adj > 1
							average = last unless initial
						else
							changefactor+=adj
							msg += " and we incremeneted the change factor by #{adj} to #{changefactor}"
						end
					end
					# If we are really outside the expected range, then we should start checking for fails
					# If not, then its a normal blip style drop and we are okay
					if curr < last/(changefactor*3)
						sustained = 0 unless failsearch

						failsearch = true unless initial
						sustained +=1
						average = last
						if sustained > NUM_BAD_RUNS && failsearch
							fail = true
						end
					else
						sustained = 0	
					end
					rfs = 2	
				#we are static
				else
					sustained+=1
					failsearch = false
					rfs = 0
					#Initially, we let things ramp up for a while before trying to find a failure
					if sustained > NUM_BAD_RUNS && initial
						initial = false
						sustained = 0
					end
					if sustained > NUM_BAD_RUNS && failsearch
						fail = true
					end	
					msg += " and we sustained, this time for #{sustained} laps"
				end
                        end
			p msg if DEBUG>0
		end
	end
end
end

#MAIN
option = ARGV.shift
if option == nil
	spawn_mongo
	spawn_ycsb(ycsb_log)
	sleep 5
else
	ycsb_log=option
end
fail = evaluate(ycsb_log)
if fail
        p "the test failed"
else
        p "the test passed"
end
