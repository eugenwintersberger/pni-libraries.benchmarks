module benchmark
    implicit none

    contains

        !----------------------------------------------------------------------
        ! compute the average over several result value
        real(kind=8) function duration_average(results)
            implicit none
            real(kind=8),dimension(:),intent(in) :: results !results

            duration_average = sum(results)/size(results)
            return 
        end function duration_average

        !----------------------------------------------------------------------
        !compute the standard deviation from the duration
        real(kind=8) function duration_error(results)
            implicit none
            real(kind=8),dimension(:),intent(in) :: results
            real(kind = 8) :: dav,error_sum

            !compute the average
            dav = duration_average(results)
            error_sum = sum((results-dav)**2)

            duration_error = sqrt(((1.d0)/(size(results)-1.d0))*error_sum)
            return 
        end function duration_error
        
        !----------------------------------------------------------------------
        subroutine print_result(title,results)
            implicit none
            character(len=*),intent(in) :: title
            real(kind=8),dimension(:),intent(in) :: results
            real(kind = 8) :: r,r_error,r_error_p

            r = duration_average(results)
            r_error = duration_error(results)
            r_error_p = r_error*100.d0/r

            write(*,*) title,r,'(+-)',r_error,'(s)',r_error_p,'(%)'
        end subroutine print_result

        !----------------------------------------------------------------------
        subroutine allocate_benchmark_results(nruns,results)
            implicit none
            integer,intent(in) :: nruns
            real(kind=8),dimension(:),allocatable,intent(inout) :: results
            integer :: mem_status

            !check if array is already allocated
            call deallocate_benchmark_results(results)

            !allocate memory
            allocate(results(nruns),stat=mem_status)
            
            results = 0.d0
        end subroutine allocate_benchmark_results


        !----------------------------------------------------------------------
        subroutine deallocate_benchmark_results(results)
            implicit none
            real(kind=8),dimension(:),allocatable,intent(inout):: results
            integer :: mem_status

            if (allocated(results)) then
               deallocate(results,stat=mem_status) 
            end if

        end subroutine deallocate_benchmark_results

        !-----------------------------------------------------------------------
        subroutine run_benchmarks(proc,results)
            implicit none
            real(kind=8),dimension(:),intent(inout) :: results
            integer :: i
            real(kind = 8) :: start_time,stop_time

            do i = 1,size(results)
                call cpu_time(start_time)
                call proc()
                call cpu_time(stop_time)
                results(i) = stop_time-start_time
                !write(*,*) start_time,stop_time,results(i)
            end do

        end subroutine run_benchmarks

end module benchmark
